/********************************************************************************
* MVP(Multicore Virtual Platform)
* (C) Copyright CASLab.EE.NCKU 2009
* All Right Reserved
*
* the RAM module of MVP emulator
*
* Shin-Ying Lee(sing@casmail.ee.ncku.edu.tw)
* Computer Architecture & System Laboratory
* Dept. of Electrical Engineering & Inst. of Computer and Communication Engineering
* National Cheng Kung University, Tainan, Taiwan
* 2009.07.05
********************************************************************************/

#include <cstring>
#include "dram.h"
//#include <bit_opt_v2.h>

#define DDR2

using namespace std;

/* the constructor */
DRAM::DRAM(uint32_t mapping_size)
{
    //make sure the size is aligned to 32-bit word
    if(mapping_size & mask(1, 0))
    {
        printf("DRAM: DRAM size is not aligned to 32-bit word\n");
    }

    bank = new uint8_t[mapping_size];

    if(bank == 0)
    {
        printf("DRAM: not enough memory space\n");
    }

	dw_bit = 0;
	bank_bit = 0;
	col_bit = 15;
	row_bit = log2(mapping_size/(pow(2,col_bit) * pow(2,bank_bit) * pow(2, dw_bit)));
	precharge_counter = 0;

	printf("DRAM: bank_bit = %d, col_bit = %d, row_bit = %d\n", bank_bit, col_bit, row_bit);

    //DRAM Model
    InitDramController();
    pre_w_burst = false;
    pre_r_burst = false;
    burst_state = NO_BURST;

    //Statstic
    accessTime = 0;
    accessB = 0;
}

DRAM::~DRAM()
{
    printf("DRAM: precharge_counter = %d\n",precharge_counter);

    if(bank != 0)
    {
        delete[]bank;
    }
}

void DRAM::InitDramController()
{
    state = IDLE;
    InitAddressDecode();
}

/* read data from the RAM module */
bool DRAM::read(uint32_t* data, uint32_t addr, int size)
{
    switch(size)
    {
        case 4:
            *data = *ptr_word(addr);
            break;
        case 1:
            *data = *ptr_byte(addr);
            break;
        case 2:
            *data = *ptr_hword(addr);
            break;
        default:
            printf("DRAM: read size error\n");
            break;
    }

    return true;
}

/* write data to the RAM module */
bool DRAM::write(uint32_t data, uint32_t addr, int size)
{
    switch(size)
    {
        case 4:
            *ptr_word(addr) = (uint32_t)data;
            break;
        case 1:
            *ptr_byte(addr) = (uint8_t)data;
            break;
        case 2:
            *ptr_hword(addr) = (uint16_t)data;
            break;
        default:
            printf("DRAM: write size error\n");
            break;
    }

    return true;
}
void DRAM::InitAddressDecode()
{
    AddrOffset_Col  = dw_bit;
    AddrOffset_Row  = AddrOffset_Col + col_bit ;
    AddrOffset_Bank = AddrOffset_Row + row_bit ;

    AddrMask_Col  = GetMask(col_bit) << AddrOffset_Col;
    AddrMask_Row  = GetMask(row_bit) << AddrOffset_Row;
    AddrMask_Bank = GetMask(bank_bit) << AddrOffset_Bank;

}

void DRAM::AddrDecode(unsigned int addr)
{
    Index_Col  = (addr & AddrMask_Col)  >> AddrOffset_Col  ;
    Index_Row  = (addr & AddrMask_Row)  >> AddrOffset_Row  ;
    Index_Bank = (addr & AddrMask_Bank) >> AddrOffset_Bank ;

    prev_Bank = Index_Bank;
    prev_Row  = Index_Row;

    //printm(d_ram,"addr %08X, row is %d",addr,Index_Row);

}

unsigned int DRAM::GetMask(unsigned int bit)
{
    switch(bit){
        case 0:     return 0x00000000;
        case 1:     return 0x00000001;
        case 2:     return 0x00000003;
        case 3:     return 0x00000007;
        case 4:     return 0x0000000F;
        case 5:     return 0x0000001F;
        case 6:     return 0x0000003F;
        case 7:     return 0x0000007F;
        case 8:     return 0x000000FF;
        case 9:     return 0x000001FF;
        case 10:    return 0x000003FF;
        case 11:    return 0x000007FF;
        case 12:    return 0x00000FFF;
        case 13:    return 0x00001FFF;
        case 14:    return 0x00003FFF;
        case 15:    return 0x00007FFF;
        case 16:    return 0x0000FFFF;
        case 17:    return 0x0001FFFF;
        case 18:    return 0x0003FFFF;
        case 19:    return 0x0007FFFF;
        case 20:    return 0x000FFFFF;
        default:    return 0x00000000;
    }
}

bool DRAM::NeedActive(unsigned int addr)
{

    unsigned int    addr_Bank;
    unsigned int    addr_Row;

    addr_Row  = (addr & AddrMask_Row)  >> AddrOffset_Row  ;
    addr_Bank = (addr & AddrMask_Bank) >> AddrOffset_Bank ;

    if(/* (addr_Bank==prev_Bank) && */(addr_Row==prev_Row) ){
        return false;
    }
    else{
        return true;
    }

}

bool DRAM::NeedPrecharge(unsigned int addr, unsigned int tRAS_count){
    if(NeedActive(addr) || tRAS_count < 10)
        return true ;
    else
        return false ;
}

bool DRAM::LocalAccess(bool write, uint32_t addr, uint32_t& data, unsigned int length,uint32_t burst_length)
{
    //uint32_t local_address = addr & get_address_mask();
    uint32_t local_address = addr;

    accessB+=length;

#ifdef DDR2
    if(burst_state == NO_BURST)
    {
        if(burst_length>1)
        {
            burst_state = FIRST_BURST;
            b_length = burst_length;
            //printf("start to Burst  = %d",burst_length);
        }
        //printf("nonBurst  = %d",burst_length);
    }
    //FSM
    if(NeedPrecharge(local_address,100))
    {
        state=PRECHARGE;
        //printm(d_ram,"need precharge");
    }
    else{
        //printm(d_ram,"do not need precharge");
    }

    while(1){
        if(state==IDLE){
            state = PRECHARGE;
        }
        if(state == RowActive){
            if(write){
                state = WRITE;
                //wait(CWL, SC_NS);
                accessTime+=CWL;
            }
            else{//read
                state = READ;
            	//wait(CL, SC_NS);
            	accessTime+=CL;
				/*cout << sc_time_stamp() << endl;
				wait(2);
				cout << sc_time_stamp() << endl;*/
            }
        }
        if(state == READ){
            if(burst_state == FIRST_BURST && (pre_r_burst == true))
            {
                //wait(CL);
                //printf("read first Burst pipeline");
                //wait(DRAM_CLK, SC_NS);
                accessTime+=DRAM_CLK;
            }
            else if(burst_state == FIRST_BURST){
                //printm(d_ram,"read first Burst");
                //wait(CL, SC_NS);
                accessTime+=CL;
            }
            else if(burst_state == BURST){
                //printf("read Burst");
                //wait(DRAM_CLK, SC_NS);
                accessTime+=DRAM_CLK;
            }
            else if(burst_state == NO_BURST)
                //wait(CL, SC_NS);
                accessTime+=CL;
            else
                //wait(CL, SC_NS);
                accessTime+=CL;
            break;
        }
        if(state == WRITE){
            if(burst_state == FIRST_BURST && (pre_w_burst == true))
            {
                //wait(CWL);
                //printf("write first Burst pipeline");
                //wait(DRAM_CLK, SC_NS);
                accessTime+=DRAM_CLK;
            }
            else if(burst_state == FIRST_BURST){
                //printf("write first Burst");
                //wait(CWL, SC_NS);
                accessTime+=CWL;
            }
            else if(burst_state == BURST){
                //printf("write Burst");
                //wait(DRAM_CLK, SC_NS);
                accessTime+=DRAM_CLK;
            }
            else if(burst_state == NO_BURST){
                //wait(CWL, SC_NS);
                accessTime+=CWL;
            }
            else
                //wait(CWL, SC_NS);
                accessTime+=CWL;
            break;
        }
        if(state == PRECHARGE){
            //wait(tRP, SC_NS);
            accessTime+=tRP;
            precharge_counter++;
            state = RowActive;
        }
    }

    if(burst_state == FIRST_BURST){
        burst_state = BURST;
        b_length--;
        if(write)
            pre_w_burst = true;
        else
            pre_r_burst = true;
    }
    else if(burst_state == BURST)
    {
        b_length--;
        if(b_length==0)
        {
            burst_state = NO_BURST;
            //printf("release Burst\n");
            if(write)
                pre_w_burst = false;
            else
                pre_r_burst = false;
		}
    }
    else
    {
        //no burst
        pre_w_burst = false;
        pre_r_burst = false;
    }
#endif

    AddrDecode(local_address);

    if(write)
    {
        return this->write(data, local_address, length);
    }
    else
    {
        return this->read(&data, local_address, length);
    }


}

