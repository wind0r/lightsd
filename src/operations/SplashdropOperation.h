#pragma once

#include <yaml-cpp/yaml.h>

#include "../hsv.h"
#include "Operation.h"

#include "../VariableStore/BoundConcreteValueType.h"
#include "../VariableStore/VariableStore.h"

class SplashdropOperation : public Operation {
  enum STATE { IDLE = 0, DROPPING, RISING_SPLASH, DEACYING_SPLASH };

  struct Drop {
    HSV color;
    float rate;
    STATE state;
  };

  std::vector<Drop> drops;

  void hitDrop(Drop& drop);

  void decayDrop(Drop& drop);

  void drawSplash(const Drop& drop,
                  const size_t index,
                  const AbstractBaseBuffer<HSV>& buffer,
                  const size_t width);

  void drawDrop(Drop&,
                const size_t index,
                const AbstractBaseBuffer<HSV>& buffer);

 public:
  SplashdropOperation(const std::string& name,
                      std::shared_ptr<VariableStore> store,
                      YAML::const_iterator start,
                      YAML::const_iterator end);

  void draw(const AbstractBaseBuffer<HSV>& buffer);

  Operation::BufferType operator()(Operation::BufferType& buffer);
};
