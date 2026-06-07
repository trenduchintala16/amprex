#ifndef TURING_OPCODE_RANK_H
#define TURING_OPCODE_RANK_H

#include <cstdint>
#include <string>
#include <unordered_map>

// Rank buckets for bias-current provisioning.
// Lower rank = lower current demand.
enum class InstrRank : uint8_t {
    RANK_0 = 0,
    RANK_1 = 1,
    RANK_2 = 2,
    RANK_3 = 3,
    RANK_4 = 4,
    RANK_5 = 5,
    RANK_6 = 6,
    UNKNOWN = 255
};

enum class SwitchType : uint8_t {
    NO = 0,
    MEDIUM = 1,
    LARGE = 2
};

// Opcode -> rank mapping for Turing / sm_75 traces.
// This is intentionally conservative: many instructions are grouped by
// functional class rather than trying to overfit per-opcode power.
static const std::unordered_map<std::string, InstrRank> kOpcodeToRank = {
    // Rank 0: simple moves / nops / predicate plumbing
    {"MOV",     InstrRank::RANK_0},
    {"MOV32I",  InstrRank::RANK_0},
    {"MOVM",    InstrRank::RANK_0},
    {"SEL",     InstrRank::RANK_0},
    {"PRMT",    InstrRank::RANK_0},
    {"P2R",     InstrRank::RANK_0},
    {"R2P",     InstrRank::RANK_0},
    {"NOP",     InstrRank::RANK_0},

    // Rank 1: light integer / logic / memory ops
    {"IADD",    InstrRank::RANK_1},
    {"IADD3",   InstrRank::RANK_1},
    {"IADD32I", InstrRank::RANK_1},
    {"LOP",     InstrRank::RANK_1},
    {"SHL",     InstrRank::RANK_1},
    {"SHR",     InstrRank::RANK_1},
    {"LD",      InstrRank::RANK_1},
    {"LDG",     InstrRank::RANK_1},
    {"LDL",     InstrRank::RANK_1},
    {"LDS",     InstrRank::RANK_1},
    {"ST",      InstrRank::RANK_1},
    {"STG",     InstrRank::RANK_1},
    {"STL",     InstrRank::RANK_1},
    {"STS",     InstrRank::RANK_1},

    // Rank 2: moderate integer / control / conversion
    {"IMUL",    InstrRank::RANK_2},
    {"IMUL32I", InstrRank::RANK_2},
    {"LEA",     InstrRank::RANK_2},
    {"LOP3",    InstrRank::RANK_2},
    {"SHF",     InstrRank::RANK_2},
    {"F2F",     InstrRank::RANK_2},
    {"F2FP",    InstrRank::RANK_2},
    {"F2I",     InstrRank::RANK_2},
    {"I2F",     InstrRank::RANK_2},
    {"I2I",     InstrRank::RANK_2},
    {"I2IP",    InstrRank::RANK_2},
    {"FRND",    InstrRank::RANK_2},
    {"BRA",     InstrRank::RANK_2},
    {"CALL",    InstrRank::RANK_2},
    {"RET",     InstrRank::RANK_2},
    {"EXIT",    InstrRank::RANK_2},
    {"YIELD",   InstrRank::RANK_2},

    // Rank 3: medium floating-point / bit ops
    {"FADD",    InstrRank::RANK_3},
    {"FADD32I", InstrRank::RANK_3},
    {"FMUL",    InstrRank::RANK_3},
    {"FMUL32I", InstrRank::RANK_3},
    {"HMUL2",   InstrRank::RANK_3},
    {"HMUL2_32I", InstrRank::RANK_3},
    {"HFMA2",   InstrRank::RANK_3},
    {"HFMA2_32I", InstrRank::RANK_3},
    {"BREV",    InstrRank::RANK_3},
    {"FLO",     InstrRank::RANK_3},
    {"POPC",    InstrRank::RANK_3},

    // Rank 4: heavier FP / special math / texture-ish paths
    {"DADD",    InstrRank::RANK_4},
    {"DMUL",    InstrRank::RANK_4},
    {"DSETP",   InstrRank::RANK_4},
    {"MUFU",    InstrRank::RANK_4},
    {"TEX",     InstrRank::RANK_4},
    {"TLD",     InstrRank::RANK_4},
    {"TLD4",    InstrRank::RANK_4},
    {"TMML",    InstrRank::RANK_4},
    {"TXD",     InstrRank::RANK_4},
    {"TXQ",     InstrRank::RANK_4},

    // Rank 5: atomics / reductions / expensive integer paths
    {"ATOM",      InstrRank::RANK_5},
    {"ATOMS",     InstrRank::RANK_5},
    {"ATOMG",     InstrRank::RANK_5},
    {"RED",       InstrRank::RANK_5},
    {"IMAD",      InstrRank::RANK_5},
    {"IDP",       InstrRank::RANK_5},
    {"IDP4A",     InstrRank::RANK_5},
    {"VABSDIFF",  InstrRank::RANK_5},
    {"VABSDIFF4", InstrRank::RANK_5},

    // Rank 6: highest-demand / fused compute / tensor ops
    {"FFMA",    InstrRank::RANK_6},
    {"FFMA32I", InstrRank::RANK_6},
    {"DFMA",    InstrRank::RANK_6},
    {"HMMA",    InstrRank::RANK_6},
    {"BMMA",    InstrRank::RANK_6},
    {"IMMA",    InstrRank::RANK_6},
};

inline InstrRank get_rank(const std::string& opcode) {
    auto it = kOpcodeToRank.find(opcode);
    return (it == kOpcodeToRank.end()) ? InstrRank::UNKNOWN : it->second;
}



inline int cluster_of(InstrRank r) {
    switch (r) {
        case InstrRank::RANK_0:
        case InstrRank::RANK_1:
        case InstrRank::RANK_2:
            return 0; // low
        case InstrRank::RANK_3:
        case InstrRank::RANK_4:
            return 1; // middle
        case InstrRank::RANK_5:
        case InstrRank::RANK_6:
            return 2; // high
        default:
            return -1;
    }
}

inline SwitchType classify_switch(InstrRank prev, InstrRank curr) {
    int p = cluster_of(prev);
    int c = cluster_of(curr);

    if (p < 0 || c < 0) return SwitchType::NO;
    if (p == c) return SwitchType::NO;
    if ((p == 0 && c == 2) || (p == 2 && c == 0)) return SwitchType::LARGE;
    return SwitchType::MEDIUM;
}

#endif  // TURING_OPCODE_RANK_H
