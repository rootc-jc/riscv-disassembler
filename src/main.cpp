#include <bits/stdc++.h>
using namespace std;

int distinct = 0;

struct instruction
{
    string instr;
    bool offset = false;
    bool contains_label = false;
    string label;
    int step;
};

void labelling(vector<instruction> unlabelled)
{
    int k = unlabelled.size();
    int i = 0;
    for (i = 0; i < k; i++)
    {
        if (unlabelled[k - 1 + unlabelled[i].step].contains_label)
        {
            unlabelled[i].instr.append(unlabelled[k - 1 + unlabelled[i].step].label);
        }
        else
        {
            /* code */
            unlabelled[k - 1 + unlabelled[i].step].label = "L" + to_string(distinct);
            distinct++;
            unlabelled[k - 1 + unlabelled[i].step].contains_label = true;
            unlabelled[i].instr.append(unlabelled[k - 1 + unlabelled[i].step].label);
        }
    }
}

vector<instruction> disassembled;

vector<int> Rformat = {0, 1, 1, 0, 0, 1, 1};
vector<int> Iformat = {0, 0, 1, 0, 0, 1, 1};
vector<int> I2format = {0, 0, 0, 0, 0, 1, 1};
vector<int> I3format = {1, 1, 0, 0, 1, 1, 1};
vector<int> Sformat = {0, 1, 0, 0, 0, 1, 1};
vector<int> Bformat = {1, 1, 0, 0, 0, 1, 1};
vector<int> Jformat = {1, 1, 0, 1, 1, 1, 1};
vector<int> Uformat = {0, 1, 1, 0, 1, 1, 1};

void print(std::vector<int> const &a)
{
    std::cout << "The vector elements are : ";

    for (int i = 0; i < a.size(); i++)
        std::cout << a.at(i) << ' ';
}

int registr(vector<int> binary)
{
    int number = 0;
    number = number + 16 * binary[0];
    number = number + 8 * binary[1];
    number = number + 4 * binary[2];
    number = number + 2 * binary[3];
    number = number + 1 * binary[4];
    return number;
}

int imm12(vector<int> binary)
{
    int number = 0;
    number = number - 2048 * binary[0];
    number = number + 1024 * binary[1];
    number = number + 512 * binary[2];
    number = number + 256 * binary[3];
    number = number + 128 * binary[4];
    number = number + 64 * binary[5];
    number = number + 32 * binary[6];
    number = number + 16 * binary[7];
    number = number + 8 * binary[8];
    number = number + 4 * binary[9];
    number = number + 2 * binary[10];
    number = number + 1 * binary[11];
    return number;
}

int imm20(vector<int> binary)
{
    int power = 1;
    int number = 0;
    for (int i = 19; i >= 0; i--)
    {
        number = number + power * binary[i];
        power = power * 2;
    }
    return number;
}

vector<int> hex_to_dec(string hex)
{
    int size = hex.length();
    vector<int> binary;
    for (int i = 0; i < size; i++)
    {
        char x = hex[i];

        if (x == '0')
        {
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(0);
        }
        else if (x == '1')
        {
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(1);
        }
        else if (x == '2')
        {
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(0);
        }
        else if (x == '3')
        {
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(1);
        }
        else if (x == '4')
        {
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(0);
        }
        else if (x == '5')
        {
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(1);
        }
        else if (x == '6')
        {
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(0);
        }
        else if (x == '7')
        {
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(1);
        }
        else if (x == '8')
        {
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(0);
        }
        else if (x == '9')
        {
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(1);
        }
        else if (x == 'a')
        {
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(0);
        }
        else if (x == 'b')
        {
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(1);
        }
        else if (x == 'c')
        {
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(0);
        }
        else if (x == 'd')
        {
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(1);
        }
        else if (x == 'e')
        {
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(0);
        }
        else if (x == 'f')
        {
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(1);
        }
    }
    return binary;
}

void R(vector<int> binary)
{
    vector<int> funct3 = {binary.end() - 15, binary.end() - 12};
    vector<int> funct7 = {binary.begin(), binary.begin() + 6};
    vector<int> rs2 = {binary.begin() + 7, binary.begin() + 12};
    vector<int> rs1 = {binary.begin() + 12, binary.begin() + 17};
    vector<int> rd = {binary.begin() + 20, binary.begin() + 25};

    instruction instruction_;

    if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 0)
    {
        if (funct7[1] == 1)
        {
            // sub
            instruction_.instr = "sub x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2));
            disassembled.push_back(instruction_);
        }
        else
        {
            // add
            instruction_.instr = "add x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2));
            disassembled.push_back(instruction_);
        }
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 0)
    {
        // xor
        instruction_.instr = "xor x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 0)
    {
        // or
        instruction_.instr = "or x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 1)
    {
        // and
        instruction_.instr = "and x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 0)
    {
        // slt
        instruction_.instr = "slt x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 1)
    {
        // sltu
        instruction_.instr = "sltu x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1)
    {
        // sll
        instruction_.instr = "sll x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 1)
    {
        // sra and srl
        if (funct7[1] = 1)
        {
            // sra
            instruction_.instr = "sra x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2));
            disassembled.push_back(instruction_);
        }
        else
        {
            // srl
            instruction_.instr = "srl x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2));
            disassembled.push_back(instruction_);
        }
    }
    else
    {
        cout << "error\n";
    }
}

void I(vector<int> binary)
{
    vector<int> funct3 = {binary.end() - 15, binary.end() - 12};
    vector<int> imm = {binary.begin(), binary.begin() + 12};
    vector<int> rs1 = {binary.begin() + 12, binary.begin() + 17};
    vector<int> rd = {binary.begin() + 20, binary.begin() + 25};

    instruction instruction_;

    if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 0)
    {
        // addi
        instruction_.instr = "addi x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", " + to_string(imm12(imm));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 0)
    {
        // xori
        instruction_.instr = "xori x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", " + to_string(imm12(imm));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 0)
    {
        // ori
        instruction_.instr = "or x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", " + to_string(imm12(imm));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 1)
    {
        // andi
        instruction_.instr = "andi x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", " + to_string(imm12(imm));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 0)
    {
        // slti
        instruction_.instr = "slti x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", " + to_string(imm12(imm));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 1)
    {
        // sltiu
        instruction_.instr = "sltiu x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", " + to_string(imm12(imm));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1)
    {
        // slli
        instruction_.instr = "slli x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", " + to_string(imm12(imm));
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 1)
    {
        // srai
        instruction_.instr = "srai x" + to_string(registr(rd)) + ", x" + to_string(registr(rs1)) + ", " + to_string(imm12(imm));
        disassembled.push_back(instruction_);
    }

    else
    {
        cout << "error\n";
    }
}

void I2(vector<int> binary)
{
    vector<int> funct3 = {binary.end() - 15, binary.end() - 12};
    vector<int> imm = {binary.begin(), binary.begin() + 12};
    vector<int> rs1 = {binary.begin() + 12, binary.begin() + 17};
    vector<int> rd = {binary.begin() + 20, binary.begin() + 25};

    instruction instruction_;

    if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 0)
    {
        // lb
        instruction_.instr = "lb x" + to_string(registr(rd)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1)
    {
        // lh
        instruction_.instr = "lh x" + to_string(registr(rd)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 0)
    {
        // lw
        instruction_.instr = "lw x" + to_string(registr(rd)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 1)
    {
        // ld
        instruction_.instr = "ld x" + to_string(registr(rd)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 0)
    {
        // lbu
        instruction_.instr = "lbu x" + to_string(registr(rd)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 1)
    {
        // lhu
        instruction_.instr = "lhu x" + to_string(registr(rd)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 0)
    {
        // lwu
        instruction_.instr = "lwu x" + to_string(registr(rd)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else
    {
        cout << "error\n";
    }
}

void I3(vector<int> binary)
{
    // jalr
    vector<int> funct3 = {binary.end() - 15, binary.end() - 12};
    vector<int> imm = {binary.begin(), binary.begin() + 12};
    vector<int> rs1 = {binary.begin() + 12, binary.begin() + 17};
    vector<int> rd = {binary.begin() + 20, binary.begin() + 25};

    instruction instruction_;

    instruction_.instr = "jalr x" + to_string(registr(rd)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
    disassembled.push_back(instruction_);
}

void S(vector<int> binary)
{
    vector<int> funct3 = {binary.end() - 15, binary.end() - 12};
    vector<int> imm_high = {binary.begin(), binary.begin() + 7};
    vector<int> rs2 = {binary.begin() + 7, binary.begin() + 12};
    vector<int> rs1 = {binary.begin() + 12, binary.begin() + 17};
    vector<int> imm_low = {binary.begin() + 20, binary.begin() + 25};
    vector<int> imm;
    imm.reserve(imm_high.size() + imm_low.size());
    imm.insert(imm.end(), imm_high.begin(), imm_high.end());
    imm.insert(imm.end(), imm_low.begin(), imm_low.end());

    instruction instruction_;

    if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 0)
    {
        // sb
        instruction_.instr = "sb x" + to_string(registr(rs2)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1)
    {
        // sh
        instruction_.instr = "sh x" + to_string(registr(rs2)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 0)
    {
        // sw
        instruction_.instr = "sw x" + to_string(registr(rs2)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 1)
    {
        // sd
        instruction_.instr = "sd x" + to_string(registr(rs2)) + ", " + to_string(imm12(imm)) + "(x" + to_string(registr(rs1)) + ")";
        disassembled.push_back(instruction_);
    }

    else
    {
        cout << "error\n";
    }
}

void B(vector<int> binary)
{
    vector<int> funct3 = {binary.end() - 15, binary.end() - 12};
    vector<int> imm_12;
    imm_12.push_back(binary[0]);
    vector<int> imm_high = {binary.begin() + 1, binary.begin() + 7};
    vector<int> rs2 = {binary.begin() + 7, binary.begin() + 12};
    vector<int> rs1 = {binary.begin() + 12, binary.begin() + 17};
    vector<int> imm_low = {binary.begin() + 20, binary.begin() + 24};
    vector<int> imm_11 = {binary[24]};
    vector<int> imm;
    imm.reserve(imm_12.size() + imm_11.size() + imm_high.size() + imm_low.size());
    imm.insert(imm.end(), imm_12.begin(), imm_12.end());
    imm.insert(imm.end(), imm_11.begin(), imm_11.end());
    imm.insert(imm.end(), imm_high.begin(), imm_high.end());
    imm.insert(imm.end(), imm_low.begin(), imm_low.end());

    instruction instruction_;

    int stepper = imm12(imm);
    stepper = stepper * 2;
    int step = stepper / 4;

    if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 0)
    {
        // beq
        instruction_.instr = "beq x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2)) + ", ";
        instruction_.step = step;
        instruction_.offset = true;
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1)
    {
        // bne
        instruction_.instr = "bne x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2)) + ", ";
        instruction_.step = step;
        instruction_.offset = true;
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 0)
    {
        // blt
        instruction_.instr = "blt x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2)) + ", ";
        instruction_.step = step;
        instruction_.offset = true;
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 1)
    {
        // bge
        instruction_.instr = "bge x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2)) + ", ";
        instruction_.step = step;
        instruction_.offset = true;
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 0)
    {
        // bltu
        instruction_.instr = "bltu x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2)) + ", ";
        instruction_.step = step;
        instruction_.offset = true;
        disassembled.push_back(instruction_);
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 1)
    {
        // bgeu
        instruction_.instr = "bgeu x" + to_string(registr(rs1)) + ", x" + to_string(registr(rs2)) + ", ";
        instruction_.step = step;
        instruction_.offset = true;
        disassembled.push_back(instruction_);
    }

    else
    {
        cout << "error\n";
    }
}

void J(vector<int> binary)
{
    vector<int> rd = {binary.begin() + 20, binary.begin() + 25};
    vector<int> imm;
    imm.push_back(binary[0]);
    for (int i = 12; i < 20; i++)
    {
        imm.push_back(binary[i]);
    }
    imm.push_back(binary[11]);
    for (int i = 1; i < 11; i++)
    {
        imm.push_back(binary[i]);
    }

    instruction instruction_;

    int stepper = imm20(imm);
    stepper = stepper * 2;
    int step = stepper / 4;

    instruction_.instr = "jal x" + to_string(registr(rd)) + ", ";
    instruction_.offset = true;
    instruction_.step = step;
    disassembled.push_back(instruction_);
}

void U(vector<int> binary, string imm)
{
    vector<int> rd = {binary.begin() + 20, binary.begin() + 25};
    instruction instruction_;
    instruction_.instr = "lui x" + to_string(registr(rd)) + ", 0x" + imm;
    disassembled.push_back(instruction_);
}

int main(int argc, char **argv)
{
    string hex;
    fstream input;

    string input_name = argv[1];
    string output_name = argv[2];

    input.open(input_name, ios::in);

    while (getline(input, hex))
    {
        vector<int> binary = hex_to_dec(hex);
        vector<int> opcode = {binary.end() - 7, binary.end()};

        if (opcode == Rformat)
        {
            R(binary);
        }

        else if (opcode == Iformat)
        {
            I(binary);
        }

        else if (opcode == I2format)
        {
            I2(binary);
        }

        else if (opcode == I3format)
        {
            I3(binary);
        }

        else if (opcode == Sformat)
        {
            S(binary);
        }

        else if (opcode == Bformat)
        {
            B(binary);
        }

        else if (opcode == Jformat)
        {
            J(binary);
        }
        else if (opcode == Uformat)
        {
            string imm = hex.substr(0, 5);
            U(binary, imm);
        }
        else
        {
            cout << "invalid opcode\n";
        }
    }
    input.close();

    int i = 0;
    for (i = 0; i < disassembled.size(); i++)
    {
        if (disassembled[i].offset)
        {
            if (disassembled[i + (disassembled[i]).step].contains_label)
            {
                (disassembled[i].instr).append(disassembled[i + disassembled[i].step].label);
            }
            else
            {
                disassembled[i + disassembled[i].step].label = "L" + to_string(distinct);
                disassembled[i + disassembled[i].step].instr = disassembled[i + disassembled[i].step].label + ": " + disassembled[i + disassembled[i].step].instr;
                distinct++;
                (disassembled[i + disassembled[i].step]).contains_label = true;
                (disassembled[i].instr).append(disassembled[i + disassembled[i].step].label);
            }
        }
    }

    fstream output;
    output.open(output_name, ios::app);
    for (int i = 0; i < disassembled.size(); i++)
    {
        output << disassembled[i].instr << "\n";
    }
    output.close();

    return 0;
}