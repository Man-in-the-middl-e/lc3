#pragma once

#include "reader.hpp"
#include <fstream>
#include <assert.h>

class Writer {
  public:
    Writer(const std::string& filename);
    void write(uint16_t instruction);
    void write(const std::string& data);

  private:
    std::ofstream m_outpuStream;
};

class Assembler {
  public:
    Assembler(std::vector<std::shared_ptr<Instruction>>& instructions);
    void gnenerate(Writer& writer);

    template <uint16_t bitcount = 9>
    static std::string toBinaryString(uint16_t number)
    {
        return std::bitset<bitcount>(number).to_string();
    }

    static bool isImmediate(const std::string& thirdOperand)
    {
        return thirdOperand.front() == '#';
    }

    template <uint16_t bitcount>
    static std::string getBinaryOffsetToJumpTo(const std::string& labelOrOffset)
    {
        if (isImmediate(labelOrOffset)) {
            return toBinaryString<bitcount>(std::stoi(labelOrOffset.substr(1)));
        }
        return Assembler::toBinaryString<bitcount>(
            SymbolTable::the().get(labelOrOffset));
    }

  private:
    std::vector<std::shared_ptr<Instruction>> m_instructions;
};