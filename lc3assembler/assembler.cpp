#include "assembler.hpp"

#include <assert.h>
#include <bitset>

Writer::Writer(const std::string& filename)
    : m_outpuStream(filename, std::ios::binary)
{
}

void Writer::write(uint16_t instruction)
{
    m_outpuStream.write(reinterpret_cast<char*>(&instruction),
                        sizeof(instruction));
}

void Writer::write(const std::string& data)
{
    m_outpuStream.write(data.c_str(), std::streamsize(data.size()));
}

Assembler::Assembler(std::vector<InstructionWithAddress>& instructions)
    : m_instructions(instructions)
{
}

void Assembler::gnenerate(Writer& writer)
{
    for (auto&& [instruction, instructionAddress] : m_instructions) {
        if (auto blkwDerective =
                dynamic_cast<BlkwDerective*>(instruction.get());
            blkwDerective) {
            for (int i = 0; i < blkwDerective->getNumberOfMemoryLocations();
                 ++i) {
                writer.write(0);
            }
        }
        else if (auto stringzDerective =
                     dynamic_cast<StringDerective*>(instruction.get());
                 stringzDerective) {
            for (auto ch : stringzDerective->getStringToWrite()) {
                std::bitset<16> sixteenBitChar(ch);
                writer.write(sixteenBitChar.to_ulong());
            }
            writer.write(0);
        } else if (dynamic_cast<EndDerective*>(instruction.get())) {
            continue;
        }
        else {
            auto binaryInstruction = instruction->generate(instructionAddress);
            writer.write(binaryInstruction);
        }
    }
}