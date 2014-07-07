#ifndef _DRAM_H_
#define _DRAM_H_

#include <cstdio>
#include <cstdint>
//#include <systemc.h>
#include <cmath>

//MICRON Mobile LPDDR
#define READ_PIPELINE
#define DDR2
#define REF_TIME    6400000 //#cycle @ 100MHz (10ns)
#define REF_CYCLE   8192
#define CL          15	//ns
#define CWL         15	//ns
#define tRAS        40   // Active to Precharge
#define tRP         15       // Precharge to Active ns
#define tRCD        15       // RAS to CAS ns
#define DRAM_CLK	5		// NS

inline const uint32_t mask(uint32_t msb, uint32_t lsb)
{
    const uint32_t t = 0xFFFFFFFF;
    return (t << lsb) & (t>>(31 - msb));
}

enum ST_SDRAM {IDLE,        // 0
               RowActive,   // 1
               READ,        // 2
               WRITE,       // 3
               PRECHARGE    // 4
               };
enum BURST_STATE{
    FIRST_BURST,
    BURST,
    NO_BURST
};

/* module of RAM */
class DRAM
{
    public:
        DRAM(uint32_t mapping_size);
        ~DRAM();

        bool read(uint32_t*, uint32_t, int);
        bool write(uint32_t, uint32_t, int);
        virtual bool LocalAccess(bool write, uint32_t addr, uint32_t& data, unsigned int length,uint32_t burst_length);

        //DRAM Model
        void InitDramController();
        bool NeedActive(unsigned int addr);
        bool NeedPrecharge(unsigned int addr, unsigned int tRAS_count);

        uint64_t accessTime;
        uint64_t accessB;


    private:

    	uint32_t mappint_size;
        uint8_t* bank;

		uint32_t bank_bit;
		uint32_t row_bit;
		uint32_t col_bit;
		uint32_t dw_bit;

        inline uint32_t* ptr_word(uint32_t addr)
        {
            return (uint32_t*)(bank + addr);
        }

        inline uint16_t* ptr_hword(uint32_t addr)
        {
            return (uint16_t*)(bank + addr);
        }

        inline uint8_t* ptr_byte(uint32_t addr)
        {
            return (uint8_t*)(bank + addr);
        }

        //DRAM Model
        ST_SDRAM        state;
        unsigned int    AddrOffset_Bank;
        unsigned int    AddrOffset_Row;
        unsigned int    AddrOffset_Col;

        unsigned int    AddrMask_Bank;
        unsigned int    AddrMask_Row;
        unsigned int    AddrMask_Col;

        unsigned int    Index_Bank;
        unsigned int    Index_Row;
        unsigned int    Index_Col;

        unsigned int    prev_Bank;
        unsigned int    prev_Row;

        void InitAddressDecode();
        void AddrDecode(unsigned int addr);
        unsigned int GetMask(unsigned int bit);

		//char dram_name[16];
        uint32_t precharge_counter;
        int b_length;
        BURST_STATE burst_state;
        int pre_burst;
        bool pre_w_burst;
        bool pre_r_burst;
};

#endif

