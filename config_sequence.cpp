#include "config_sequence.h"
#include "config.h"
#include "operations/RainbowOperation.h"
#include "operations/RotateOperation.h"
#include "operations/RaindropOperation.h"
#include "operations/BellOperation.h"
#include "operations/SplashdropOperation.h"
#include "operations/HSVUDPInputOperation.h"
#include "operations/ShadeOperation.h"
#include "operations/SolidColorOperation.h"
#include "operations/FadeOperation.h"
#include "operations/lua/LuaOperation.h"
#include "operations/GameOfLifeOperation.h"


struct SequenceGenerator {
        using IterT=YAML::const_iterator;
        using GenT = std::unique_ptr<Operation>;
        virtual GenT operator()(VariableStore&, IterT, IterT) const = 0;
};

template<typename T>
struct SSequenceGenerator : SequenceGenerator {
        using ParentT = SequenceGenerator;
//using IterT= typename ParentT::IterT;
        using Self = SSequenceGenerator<T>;
        inline static std::unique_ptr<ParentT> build() {
                return std::make_unique<Self>();
        }
        virtual GenT operator()(VariableStore &store, IterT begin, IterT end) const {
                return std::make_unique<T>(store, begin, end);
        }
};

std::unique_ptr<Operation>
generateSequenceStep(VariableStore &store, const std::string &step_type, YAML::const_iterator begin, YAML::const_iterator end) {
    using GeneratorType = std::unique_ptr<SequenceGenerator>;

    static std::map<std::string, GeneratorType> types = []() {
            std::map<std::string, GeneratorType> types;
            types["fade"] = SSequenceGenerator<FadeOperation>::build();
            types["bell"] = SSequenceGenerator<BellOperation>::build();
            types["gameoflife"] = SSequenceGenerator<GameOfLifeOperation>::build();
            types["hsvudpinput"] = SSequenceGenerator<HSVUDPInputOperation>::build();
            types["initrainbow"] = SSequenceGenerator<RainbowOperation>::build();
            types["initsolidcolor"] = SSequenceGenerator<SolidColorOperation>::build();
            types["lua"] = SSequenceGenerator<LuaOperation>::build();
            types["raindrop"] = SSequenceGenerator<RaindropOperation>::build();
            types["rotate"] = SSequenceGenerator<RotateOperation>::build();
            types["shade"] = SSequenceGenerator<ShadeOperation>::build();
            types["splashdrop"] = SSequenceGenerator<SplashdropOperation>::build();
            types["udpinput"] = SSequenceGenerator<HSVUDPInputOperation>::build();
            return types;
    }();

    const auto lower_case_name = boost::algorithm::to_lower_copy(step_type);
    const auto it = types.find(lower_case_name);

    if (it == types.end()) {
        throw ConfigParsingException("The selected step_type wasn't found.");
    } else {
        auto& func = *(it->second);
        return func(store, begin, end);
    }
}

void
parseSequence(VariableStore &store, std::vector<std::unique_ptr<Operation>> &steps, const YAML::Node &sequence_node) {
    assert(sequence_node.Type() == YAML::NodeType::Sequence);

    for (const auto node : sequence_node) {
        switch (node.Type()) {
            case YAML::NodeType::Scalar: {
                const std::string step_name = node.as<std::string>();

                auto step = generateSequenceStep(store, step_name, node.end(),
                                                 node.end());
                steps.push_back(std::move(step));
                break;

            }
            case YAML::NodeType::Map: {

                for (const auto &map_entry  : node) {
                    const std::string step_name = map_entry.first.as<std::string>();
                    std::cout << step_name << std::endl;


                    switch (map_entry.second.Type()) {
                        case YAML::NodeType::Map: {
                            auto step = generateSequenceStep(store, step_name, map_entry.second.begin(),
                                                             map_entry.second.end());
                            steps.push_back(std::move(step));
                            break;
                        }
                        default:
                            std::cout << map_entry.second.Type() << std::endl;
                            throw ConfigParsingException("Invalid node in sequence.");
                    }

                }

                break;
            }
            case YAML::NodeType::Sequence:
            case YAML::NodeType::Undefined:
            case YAML::NodeType::Null:
                throw ConfigParsingException("Invalid node in sequence.");
        }
    }
}

