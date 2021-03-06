#ifndef GEEBEE_SRC_CPU_H
#define GEEBEE_SRC_CPU_H

#include <array>
#include <functional>

#include "Joypad.h"
#include "LCD.h"
#include "Memory.h"
#include "Timer.h"
#include "types.h"

namespace gb {

class LCD;
class Program;
class Window;

class CPU {
 public:
  CPU(Window& window, const Program& program);
  ~CPU() = default;

  Memory& memory() { return memory_; }
  Joypad& joypad() { return joypad_; }
  void reset();
  void cycle();
  void step();

  void printState();

 private:
  using Opcodes = std::array<std::function<int()>, 0x100>;

  static const std::array<std::string, 0x100> opcode_description_;
  static const std::array<std::string, 0x100> prefix_opcode_description_;

  void initNoboot();

  void setupOpcodes();
  void setupCbOpcodes();
  int readInstruction();

  int handleOpcode(Byte op);
  void clearFlags();
  void serializeFlags();
  void deserializeFlags();

  int load16Data(Byte& high, Byte& low);

  int write16DataAddress();
  int load16DataAddress();

  int jumpRelative8Data(bool jump);
  int jump16Data(bool jump);
  int call16Data(bool jump);
  int ret(bool jump);

  int inc(Byte& byte);
  int dec(Byte& byte);
  int addHl(Word word);
  int add(Byte byte);
  int addCarry(Byte byte);
  int sub(Byte byte);
  int subCarry(Byte byte);

  int compare(Byte byte);

  int handleAnd(Byte byte);
  int handleXor(Byte byte);
  int handleOr(Byte byte);

  int handleSwap(Byte& byte);
  int handleBit(int bit, Byte byte);
  int handleRes(int bit, Byte& byte);
  int handleSet(int bit, Byte& byte);

  int handleRst(Byte offset);

  int pop(Byte& high, Byte& low);
  int push(Byte high, Byte low);

  int add8Stack();

  int rotateLeft(Byte& byte);
  int rotateLeftCarry(Byte& byte);
  int rotateRight(Byte& byte);
  int rotateRightCarry(Byte& byte);
  int shiftLeftLogical(Byte& byte);
  int shiftRightLogical(Byte& byte);
  int shiftRight(Byte& byte);

  int daa();

  const Program& program_;
  Memory memory_;
  Joypad joypad_;
  Timer timer_;
  LCD lcd_;

  Opcodes opcodes_;
  Opcodes cb_opcodes_;

  Byte a_{0};
  Byte f_{0};
  Byte b_{0};
  Byte c_{0};
  Byte d_{0};
  Byte e_{0};
  Byte h_{0};
  Byte l_{0};

  Word sp_{0};
  Word pc_{0};

  bool interrupts_{false};
  bool halt_{false};
  bool zero_{false};
  bool add_{false};
  bool half_carry_{false};
  bool carry_{false};

  bool output_{false};
};

}  // namespace gb

#endif
