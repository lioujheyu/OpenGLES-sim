#ifndef CONTEXT_LINK_GLAPI_H_INCLUDED
#define CONTEXT_LINK_GLAPI_H_INCLUDED

#define CG_IN	1
#define CG_OUT	2

/** @defgroup
 *	@brief Instruction operand/result type
 *	@{
 */
#define INST_NO_TYPE				0
#define INST_ATTRIB					1
#define INST_UNIFORM				2
#define INST_COLOR					3
#define INST_REG					4
#define INST_CONSTANT				5
/**	@} */

/** @defgroup
 *	@brief Instruction OP code
 *	@{
 */
#define OP_ABS		0x1
#define OP_CEIL		0x2
#define OP_FLR		0x3
#define OP_FRC		0x4
#define OP_I2F		0x5
#define OP_LIT		0x6
#define OP_MOV		0x7
#define OP_NOT		0x8
#define OP_NRM		0x9
#define OP_PK2H		0xa
#define OP_PK2US	0xb
#define OP_PK4B		0xc
#define OP_PK4UB	0xd
#define OP_ROUND	0xe
#define OP_SSG		0xf
#define OP_TRUNC	0x10
#define OP_COS		0x11
#define OP_EX2		0x12
#define OP_LG2		0x13
#define OP_RCC		0x14
#define OP_RCP		0x15
#define OP_RSQ		0x16
#define OP_SCS		0x17
#define OP_SIN		0x18
#define OP_UP2H		0x19
#define OP_UP2US	0x1a
#define OP_UP4B		0x1b
#define OP_UP4UB	0x1c
#define OP_DIV		0x1d
#define OP_SHL		0x1e
#define OP_SHR		0x1f
#define OP_MOD		0x20
#define OP_ADD		0x21
#define OP_AND		0x22
#define OP_DP3		0x23
#define OP_DP4		0x24
#define OP_DPH		0x25
#define OP_DST		0x26
#define OP_MAX		0x27
#define OP_MIN		0x28
#define OP_MUL		0x29
#define OP_OR		0x2a
#define OP_RFL		0x2b
#define OP_SEQ		0x2c
#define OP_SFL		0x2d
#define OP_SGE		0x2e
#define OP_SGT		0x2f
#define OP_SLE		0x30
#define OP_SLT		0x31
#define OP_SNE		0x32
#define OP_STR		0x33
#define OP_SUB		0x34
#define OP_XPD		0x35
#define OP_DP2		0x36
#define OP_XOR		0x37
#define OP_CMP		0x38
#define OP_DP2A		0x39
#define OP_LRP		0x3a
#define OP_MAD		0x3b
#define OP_SAD		0x3c
#define OP_X2D		0x3d
#define OP_TEX		0x3e
#define OP_TXB		0x3f
#define OP_TXF		0x40
#define OP_TXL		0x41
#define OP_TXP		0x42
#define OP_TXQ		0x43
#define OP_TXD		0x44
#define OP_CAL		0x45
#define OP_RET		0x46
#define OP_BRK		0x47
#define OP_CONT		0x48
#define OP_IF		0x49
#define OP_REP		0x4a
#define OP_ELSE		0x4b
#define OP_ENDIF	0x4c
#define OP_ENDREP	0x4d
#define OP_POW		0x4e
#define OP_SWZ		0x4f
/**	@} */

/** @defgroup
 *	@brief Instruction OPCODE Modifier
 *	@{
 */
#define OPM_F		0x1
#define OPM_U		0x2
#define OPM_S		0x3
#define OPM_CC		0x4
#define OPM_CC0		0x5
#define OPM_CC1		0x6
#define OPM_SAT		0x7
#define OPM_SSAT	0x8
#define OPM_NTC		0x9
#define OPM_S24		0xa
#define OPM_U24		0xb
#define OPM_HI		0xc
/**	@} */

/** @defgroup
 *	@brief Instruction Texture Target
 *	@{
 */
#define TT_1D				0x1
#define TT_2D				0x2
#define TT_3D				0x3
#define TT_CUBE				0x4
#define TT_RECT				0x5
#define TT_SHADOW1D			0x6
#define TT_SHADOW2D			0x7
#define TT_SHADOWRECT		0x8
#define TT_ARRAY1D			0x9
#define TT_ARRAY2D			0xa
#define TT_SHADOWCUBE		0xb
#define TT_SHADOWARRAY1D	0xc
#define TT_SHADOWARRAY2D	0xd
/**	@} */

/** @defgroup
 *	@brief Instruction CC Mask
 *	@{
 */
#define CC_EQ		0x1
#define CC_GE		0x2
#define CC_GT		0x3
#define CC_LE		0x4
#define CC_LT		0x5
#define CC_NE		0x6
#define CC_TR		0x7
#define CC_FL		0x8
#define CC_EQ0		0x9
#define CC_GE0		0xa
#define CC_GT0		0xb
#define CC_LE0		0xc
#define CC_LT0		0xd
#define CC_NE0		0xe
#define CC_TR0		0xf
#define CC_FL0		0x10
#define CC_EQ1		0x11
#define CC_GE1		0x12
#define CC_GT1		0x13
#define CC_LE1		0x14
#define CC_LT1		0x15
#define CC_NE1		0x16
#define CC_TR1		0x17
#define CC_FL1		0x18
#define CC_NAN		0x19
#define CC_NAN0		0x1a
#define CC_NAN1		0x1b
#define CC_LEG		0x1c
#define CC_LEG0		0x1d
#define CC_LEG1		0x1e
#define CC_CF		0x1f
#define CC_CF0		0x20
#define CC_CF1		0x21
#define CC_NCF		0x22
#define CC_NCF0		0x23
#define CC_NCF1		0x24
#define CC_OF		0x25
#define CC_OF0		0x26
#define CC_OF1		0x27
#define CC_NOF		0x28
#define CC_NOF0		0x29
#define CC_NOF1		0x2a
#define CC_AB		0x2b
#define CC_AB0		0x2c
#define CC_AB1		0x2d
#define CC_BLE		0x2e
#define CC_BLE0		0x2f
#define CC_BLE1		0x30
#define CC_SF		0x31
#define CC_SF0		0x32
#define CC_SF1		0x33
#define CC_NSF		0x34
#define CC_NSF0		0x35
#define CC_NSF1		0x36
/**	@} */

#endif // CONTEXT_LINK_GLAPI_H_INCLUDED
