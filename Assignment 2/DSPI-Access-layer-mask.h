/*Assignment 2
MPC5510 DSPI Peripheral Access Layer
Author: HauLD3
*/

/* ---Access layer-----*/
typedef struct {
    uint32_t MCR    /* DSPI module configuration registe (4 bytes at offset 0x0000)*/
    uint32_t Reserved_0x0004    /*  (4 bytes at offset 0x0004)*/
    uint32_t TCR    /* DSPI transfer count register (4 bytes at offset 0x0008)*/
    uint32_t CTAR0    /* DSPI clock and transfer attributes register 0 (4 bytes at offset 0x000c)*/
    uint32_t CTAR1    /* DSPI clock and transfer attributes register 1 (4 bytes at offset 0x0010)*/
    uint32_t CTAR2    /* DSPI clock and transfer attributes register 2 (4 bytes at offset 0x0014)*/
    uint32_t CTAR3    /* DSPI clock and transfer attributes register 3 (4 bytes at offset 0x0018)*/
    uint32_t CTAR4    /* DSPI clock and transfer attributes register 4 (4 bytes at offset 0x001c)*/
    uint32_t CTAR5    /* DSPI clock and transfer attributes register 5 (4 bytes at offset 0x0020)*/
    uint32_t CTAR6    /* DSPI clock and transfer attributes register 6 (4 bytes at offset 0x0024)*/
    uint32_t CTAR7    /* DSPI clock and transfer attributes register 7 (4 bytes at offset 0x0028)*/
    uint32_t SR    /* DSPI status register (4 bytes at offset 0x002c)*/
    uint32_t RSER    /*  DSPI DMA/interrupt request select and enable register (4 bytes at offset 0x0030)*/
    uint32_t PUSHR    /* DSPI push TX FIFO register (4 bytes at offset 0x0034)*/
    uint32_t POPR    /* DSPI pop RX FIFO register (4 bytes at offset 0x0038)*/
    uint32_t TXFR0    /* DSPI transmit FIFO register 0 (4 bytes at offset 0x003c)*/
    uint32_t TXFR1    /* DSPI transmit FIFO register 1 (4 bytes at offset 0x0040)*/
    uint32_t TXFR2    /* DSPI transmit FIFO register 2 (4 bytes at offset 0x0044)*/
    uint32_t TXFR3    /* DSPI transmit FIFO register 3 (4 bytes at offset 0x0048)*/
    uint8_t Reserved_0x004C[48]    /*  (48 bytes at offset 0x004c)*/
    uint32_t RXFR0    /* DSPI receive FIFO register 0 (4 bytes at offset 0x007c)*/
    uint32_t RXFR1    /* DSPI receive FIFO register 1 (4 bytes at offset 0x0080)*/
    uint32_t RXFR2    /* DSPI receive FIFO register 2 (4 bytes at offset 0x0084)*/
    uint32_t RXFR3    /* DSPI receive FIFO register 3 (4 bytes at offset 0x0088)*/
    uint8_t Reserved_0x008c[48]    /*  (48 bytes at offset 0x008c)*/
    uint32_t DSICR    /* DSPI DSI configuration register (4 bytes at offset 0x00bc)*/
    uint32_t SDR    /*  DSPI DSI serialization data register (4 bytes at offset 0x00c0)*/
    uint32_t ASDR    /* DSPI DSI alternate serialization data register (4 bytes at offset 0x00c4)*/
    uint32_t COMPR    /* DSPI DSI transmit comparison register (4 bytes at offset 0x00c8)*/
    uint32_t DDR    /* DSPI DSI deserialization data register (4 bytes at offset 0x00CC)*/
} DSPI_type;

/*---- Pointer----- */
#define DSPI_A_BASE    0xFFF90000
#define DSPI_B_BASE    0xFFF94000
#define DSPI_C_BASE    0xFFF98000
#define DSPI_D_BASE    0xFFF9C000

#define DSPI_A    ((DSPI_type *)DSPI_A_BASE)
#define DSPI_B    ((DSPI_type *)DSPI_B_BASE)
#define DSPI_C    ((DSPI_type *)DSPI_C_BASE)
#define DSPI_D    ((DSPI_type *)DSPI_D_BASE)

/* -----Register mask----- */
/* MCR */
#define DSPI_MCR_MSTR_MASK    (0x1U)
#define DSPI_MCR_MSTR_SHIFT    (0U)
#define DSPI_MCR_MSTR(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_MSTR_SHIFT)) & DSPI_MSTR_MASK)

#define DSPI_MCR_CONT_SCKE_MASK    (0x2U)
#define DSPI_MCR_CONT_SCKE_SHIFT    (1U)
#define DSPI_MCR_CONT_SCKE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_CONT_SCKE_SHIFT)) & DSPI_CONT_SCKE_MASK)

#define DSPI_MCR_DCONF_MASK    (0xCU)
#define DSPI_MCR_DCONF_SHIFT    (2U)
#define DSPI_MCR_DCONF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DCONF_SHIFT)) & DSPI_DCONF_MASK)

#define DSPI_MCR_FRZ _MASK    (0x10U)
#define DSPI_MCR_FRZ _SHIFT    (4U)
#define DSPI_MCR_FRZ (x)    (((uint32_t)(((uint32_t)(x)) << DSPI_FRZ _SHIFT)) & DSPI_FRZ _MASK)

#define DSPI_MCR_MTFE_MASK    (0x20U)
#define DSPI_MCR_MTFE_SHIFT    (5U)
#define DSPI_MCR_MTFE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_MTFE_SHIFT)) & DSPI_MTFE_MASK)

#define DSPI_MCR_PCSSE_MASK    (0x40U)
#define DSPI_MCR_PCSSE_SHIFT    (6U)
#define DSPI_MCR_PCSSE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCSSE_SHIFT)) & DSPI_PCSSE_MASK)

#define DSPI_MCR_ROOE_MASK    (0x80U)
#define DSPI_MCR_ROOE_SHIFT    (7U)
#define DSPI_MCR_ROOE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_ROOE_SHIFT)) & DSPI_ROOE_MASK)

#define DSPI_MCR_PCSIS5_MASK    (0x400U)
#define DSPI_MCR_PCSIS5_SHIFT    (10U)
#define DSPI_MCR_PCSIS5(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCSIS5_SHIFT)) & DSPI_PCSIS5_MASK)

#define DSPI_MCR_PCSIS4_MASK    (0x800U)
#define DSPI_MCR_PCSIS4_SHIFT    (11U)
#define DSPI_MCR_PCSIS4(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCSIS4_SHIFT)) & DSPI_PCSIS4_MASK)

#define DSPI_MCR_PCSIS3_MASK    (0x1000U)
#define DSPI_MCR_PCSIS3_SHIFT    (12U)
#define DSPI_MCR_PCSIS3(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCSIS3_SHIFT)) & DSPI_PCSIS3_MASK)

#define DSPI_MCR_PCSIS2_MASK    (0x2000U)
#define DSPI_MCR_PCSIS2_SHIFT    (13U)
#define DSPI_MCR_PCSIS2(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCSIS2_SHIFT)) & DSPI_PCSIS2_MASK)

#define DSPI_MCR_PCSIS1_MASK    (0x4000U)
#define DSPI_MCR_PCSIS1_SHIFT    (14U)
#define DSPI_MCR_PCSIS1(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCSIS1_SHIFT)) & DSPI_PCSIS1_MASK)

#define DSPI_MCR_PCSIS0_MASK    (0x8000U)
#define DSPI_MCR_PCSIS0_SHIFT    (15U)
#define DSPI_MCR_PCSIS0(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCSIS0_SHIFT)) & DSPI_PCSIS0_MASK)

#define DSPI_MCR_MDIS_MASK    (0x20000U)
#define DSPI_MCR_MDIS_SHIFT    (17U)
#define DSPI_MCR_MDIS(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_MDIS_SHIFT)) & DSPI_MDIS_MASK)

#define DSPI_MCR_DIS_TXF_MASK    (0x40000U)
#define DSPI_MCR_DIS_TXF_SHIFT    (18U)
#define DSPI_MCR_DIS_TXF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DIS_TXF_SHIFT)) & DSPI_DIS_TXF_MASK)

#define DSPI_MCR_DIS_RXF_MASK    (0x80000U)
#define DSPI_MCR_DIS_RXF_SHIFT    (19U)
#define DSPI_MCR_DIS_RXF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DIS_RXF_SHIFT)) & DSPI_DIS_RXF_MASK)

#define DSPI_MCR_CLR_TXF_MASK    (0x100000U)
#define DSPI_MCR_CLR_TXF_SHIFT    (20U)
#define DSPI_MCR_CLR_TXF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_CLR_TXF_SHIFT)) & DSPI_CLR_TXF_MASK)

#define DSPI_MCR_CLR_RXF_MASK    (0x200000U)
#define DSPI_MCR_CLR_RXF_SHIFT    (21U)
#define DSPI_MCR_CLR_RXF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_CLR_RXF_SHIFT)) & DSPI_CLR_RXF_MASK)

#define DSPI_MCR_SMPL_PT_MASK    (0xC00000U)
#define DSPI_MCR_SMPL_PT_SHIFT    (22U)
#define DSPI_MCR_SMPL_PT(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_SMPL_PT_SHIFT)) & DSPI_SMPL_PT_MASK)

#define DSPI_MCR_HALT_MASK    (0x80000000U)
#define DSPI_MCR_HALT_SHIFT    (31U)
#define DSPI_MCR_HALT(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_HALT_SHIFT)) & DSPI_HALT_MASK)

/* TCR */
#define DSPI_TCR_SPI_TCNT_MASK    (0xFFFFU)
#define DSPI_TCR_SPI_TCNT_SHIFT    (0U)
#define DSPI_TCR_SPI_TCNT(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_SPI_TCNT_SHIFT)) & DSPI_SPI_TCNT_MASK)

/* DSPI_CTARn */
#define DSPI_DSPI_CTARn_DBR_MASK    (0x1U)
#define DSPI_DSPI_CTARn_DBR_SHIFT    (0U)
#define DSPI_DSPI_CTARn_DBR(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DBR_SHIFT)) & DSPI_DBR_MASK)

#define DSPI_DSPI_CTARn_FMSZ_MASK    (0x1EU)
#define DSPI_DSPI_CTARn_FMSZ_SHIFT    (1U)
#define DSPI_DSPI_CTARn_FMSZ(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_FMSZ_SHIFT)) & DSPI_FMSZ_MASK)

#define DSPI_DSPI_CTARn_CPOL_MASK    (0x20U)
#define DSPI_DSPI_CTARn_CPOL_SHIFT    (5U)
#define DSPI_DSPI_CTARn_CPOL(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_CPOL_SHIFT)) & DSPI_CPOL_MASK)

#define DSPI_DSPI_CTARn_CPHA_MASK    (0x40U)
#define DSPI_DSPI_CTARn_CPHA_SHIFT    (6U)
#define DSPI_DSPI_CTARn_CPHA(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_CPHA_SHIFT)) & DSPI_CPHA_MASK)

#define DSPI_DSPI_CTARn_LSBFE_MASK    (0x80U)
#define DSPI_DSPI_CTARn_LSBFE_SHIFT    (7U)
#define DSPI_DSPI_CTARn_LSBFE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_LSBFE_SHIFT)) & DSPI_LSBFE_MASK)

#define DSPI_DSPI_CTARn_PCSSCK_MASK    (0x300U)
#define DSPI_DSPI_CTARn_PCSSCK_SHIFT    (8U)
#define DSPI_DSPI_CTARn_PCSSCK(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCSSCK_SHIFT)) & DSPI_PCSSCK_MASK)

#define DSPI_DSPI_CTARn_PASC_MASK    (0xC00U)
#define DSPI_DSPI_CTARn_PASC_SHIFT    (10U)
#define DSPI_DSPI_CTARn_PASC(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PASC_SHIFT)) & DSPI_PASC_MASK)

#define DSPI_DSPI_CTARn_PDT_MASK    (0x3000U)
#define DSPI_DSPI_CTARn_PDT_SHIFT    (12U)
#define DSPI_DSPI_CTARn_PDT(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PDT_SHIFT)) & DSPI_PDT_MASK)

#define DSPI_DSPI_CTARn_PBR_MASK    (0xC000U)
#define DSPI_DSPI_CTARn_PBR_SHIFT    (14U)
#define DSPI_DSPI_CTARn_PBR(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PBR_SHIFT)) & DSPI_PBR_MASK)

#define DSPI_DSPI_CTARn_CSSCK_MASK    (0xF0000U)
#define DSPI_DSPI_CTARn_CSSCK_SHIFT    (16U)
#define DSPI_DSPI_CTARn_CSSCK(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_CSSCK_SHIFT)) & DSPI_CSSCK_MASK)

#define DSPI_DSPI_CTARn_ASC_MASK    (0xF00000U)
#define DSPI_DSPI_CTARn_ASC_SHIFT    (20U)
#define DSPI_DSPI_CTARn_ASC(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_ASC_SHIFT)) & DSPI_ASC_MASK)

#define DSPI_DSPI_CTARn_DT_MASK    (0xF000000U)
#define DSPI_DSPI_CTARn_DT_SHIFT    (24U)
#define DSPI_DSPI_CTARn_DT(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DT_SHIFT)) & DSPI_DT_MASK)

#define DSPI_DSPI_CTARn_BR_MASK    (0xF0000000U)
#define DSPI_DSPI_CTARn_BR_SHIFT    (28U)
#define DSPI_DSPI_CTARn_BR(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_BR_SHIFT)) & DSPI_BR_MASK)

/* SR */
#define DSPI_SR_TCF_MASK    (0x1U)
#define DSPI_SR_TCF_SHIFT    (0U)
#define DSPI_SR_TCF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TCF_SHIFT)) & DSPI_TCF_MASK)

#define DSPI_SR_TXRXS_MASK    (0x2U)
#define DSPI_SR_TXRXS_SHIFT    (1U)
#define DSPI_SR_TXRXS(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TXRXS_SHIFT)) & DSPI_TXRXS_MASK)

#define DSPI_SR_EOQF_MASK    (0x8U)
#define DSPI_SR_EOQF_SHIFT    (3U)
#define DSPI_SR_EOQF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_EOQF_SHIFT)) & DSPI_EOQF_MASK)

#define DSPI_SR_TFUF_MASK    (0x10U)
#define DSPI_SR_TFUF_SHIFT    (4U)
#define DSPI_SR_TFUF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TFUF_SHIFT)) & DSPI_TFUF_MASK)

#define DSPI_SR_TFFF_MASK    (0x40U)
#define DSPI_SR_TFFF_SHIFT    (6U)
#define DSPI_SR_TFFF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TFFF_SHIFT)) & DSPI_TFFF_MASK)

#define DSPI_SR_RFOF_MASK    (0x1000U)
#define DSPI_SR_RFOF_SHIFT    (12U)
#define DSPI_SR_RFOF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_RFOF_SHIFT)) & DSPI_RFOF_MASK)

#define DSPI_SR_RFDF_MASK    (0x4000U)
#define DSPI_SR_RFDF_SHIFT    (14U)
#define DSPI_SR_RFDF(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_RFDF_SHIFT)) & DSPI_RFDF_MASK)

#define DSPI_SR_TXCTR_MASK    (0xF0000U)
#define DSPI_SR_TXCTR_SHIFT    (16U)
#define DSPI_SR_TXCTR(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TXCTR_SHIFT)) & DSPI_TXCTR_MASK)

#define DSPI_SR_TXNXTPRT_MASK    (0xF00000U)
#define DSPI_SR_TXNXTPRT_SHIFT    (20U)
#define DSPI_SR_TXNXTPRT(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TXNXTPRT_SHIFT)) & DSPI_TXNXTPRT_MASK)

#define DSPI_SR_RXCTR_MASK    (0xF000000U)
#define DSPI_SR_RXCTR_SHIFT    (24U)
#define DSPI_SR_RXCTR(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_RXCTR_SHIFT)) & DSPI_RXCTR_MASK)

#define DSPI_SR_POPNXTPTR_MASK    (0xF0000000U)
#define DSPI_SR_POPNXTPTR_SHIFT    (28U)
#define DSPI_SR_POPNXTPTR(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_POPNXTPTR_SHIFT)) & DSPI_POPNXTPTR_MASK)

/* RSER */
#define DSPI_RSER_TCF_RE_MASK    (0x1U)
#define DSPI_RSER_TCF_RE_SHIFT    (0U)
#define DSPI_RSER_TCF_RE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TCF_RE_SHIFT)) & DSPI_TCF_RE_MASK)

#define DSPI_RSER_EOQF_RE_MASK    (0x8U)
#define DSPI_RSER_EOQF_RE_SHIFT    (3U)
#define DSPI_RSER_EOQF_RE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_EOQF_RE_SHIFT)) & DSPI_EOQF_RE_MASK)

#define DSPI_RSER_TFUF_RE_MASK    (0x10U)
#define DSPI_RSER_TFUF_RE_SHIFT    (4U)
#define DSPI_RSER_TFUF_RE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TFUF_RE_SHIFT)) & DSPI_TFUF_RE_MASK)

#define DSPI_RSER_TFFF_RE_MASK    (0x40U)
#define DSPI_RSER_TFFF_RE_SHIFT    (6U)
#define DSPI_RSER_TFFF_RE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TFFF_RE_SHIFT)) & DSPI_TFFF_RE_MASK)

#define DSPI_RSER_TFFF_DIRS_MASK    (0x80U)
#define DSPI_RSER_TFFF_DIRS_SHIFT    (7U)
#define DSPI_RSER_TFFF_DIRS(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TFFF_DIRS_SHIFT)) & DSPI_TFFF_DIRS_MASK)

#define DSPI_RSER_RFOF_RE_MASK    (0x1000U)
#define DSPI_RSER_RFOF_RE_SHIFT    (12U)
#define DSPI_RSER_RFOF_RE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_RFOF_RE_SHIFT)) & DSPI_RFOF_RE_MASK)

#define DSPI_RSER_RFDF_RE_MASK    (0x4000U)
#define DSPI_RSER_RFDF_RE_SHIFT    (14U)
#define DSPI_RSER_RFDF_RE(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_RFDF_RE_SHIFT)) & DSPI_RFDF_RE_MASK)

#define DSPI_RSER_RFDF_DIRS_MASK    (0x8000U)
#define DSPI_RSER_RFDF_DIRS_SHIFT    (15U)
#define DSPI_RSER_RFDF_DIRS(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_RFDF_DIRS_SHIFT)) & DSPI_RFDF_DIRS_MASK)

/* PUSHR */
#define DSPI_PUSHR_CONT_MASK    (0x1U)
#define DSPI_PUSHR_CONT_SHIFT    (0U)
#define DSPI_PUSHR_CONT(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_CONT_SHIFT)) & DSPI_CONT_MASK)

#define DSPI_PUSHR_CTAS_MASK    (0xEU)
#define DSPI_PUSHR_CTAS_SHIFT    (1U)
#define DSPI_PUSHR_CTAS(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_CTAS_SHIFT)) & DSPI_CTAS_MASK)

#define DSPI_PUSHR_EOQ_MASK    (0x10U)
#define DSPI_PUSHR_EOQ_SHIFT    (4U)
#define DSPI_PUSHR_EOQ(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_EOQ_SHIFT)) & DSPI_EOQ_MASK)

#define DSPI_PUSHR_CTCNT_MASK    (0x20U)
#define DSPI_PUSHR_CTCNT_SHIFT    (5U)
#define DSPI_PUSHR_CTCNT(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_CTCNT_SHIFT)) & DSPI_CTCNT_MASK)

#define DSPI_PUSHR_PCS5_MASK    (0x400U)
#define DSPI_PUSHR_PCS5_SHIFT    (10U)
#define DSPI_PUSHR_PCS5(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCS5_SHIFT)) & DSPI_PCS5_MASK)

#define DSPI_PUSHR_PCS4_MASK    (0x800U)
#define DSPI_PUSHR_PCS4_SHIFT    (11U)
#define DSPI_PUSHR_PCS4(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCS4_SHIFT)) & DSPI_PCS4_MASK)

#define DSPI_PUSHR_PCS3_MASK    (0x1000U)
#define DSPI_PUSHR_PCS3_SHIFT    (12U)
#define DSPI_PUSHR_PCS3(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCS3_SHIFT)) & DSPI_PCS3_MASK)

#define DSPI_PUSHR_PCS2_MASK    (0x2000U)
#define DSPI_PUSHR_PCS2_SHIFT    (13U)
#define DSPI_PUSHR_PCS2(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCS2_SHIFT)) & DSPI_PCS2_MASK)

#define DSPI_PUSHR_PCS1_MASK    (0x4000U)
#define DSPI_PUSHR_PCS1_SHIFT    (14U)
#define DSPI_PUSHR_PCS1(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCS1_SHIFT)) & DSPI_PCS1_MASK)

#define DSPI_PUSHR_PCS0_MASK    (0x8000U)
#define DSPI_PUSHR_PCS0_SHIFT    (15U)
#define DSPI_PUSHR_PCS0(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_PCS0_SHIFT)) & DSPI_PCS0_MASK)

#define DSPI_PUSHR_TXDATA_MASK    (0xFFFF0000U)
#define DSPI_PUSHR_TXDATA_SHIFT    (16U)
#define DSPI_PUSHR_TXDATA(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TXDATA_SHIFT)) & DSPI_TXDATA_MASK)

/* POPR */
#define DSPI_POPR_RXDATA_MASK    (0xFFFF0000U)
#define DSPI_POPR_RXDATA_SHIFT    (16U)
#define DSPI_POPR_RXDATA(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_RXDATA_SHIFT)) & DSPI_RXDATA_MASK)

/* TXFRn */
#define DSPI_TXFRn_TXCMD_MASK    (0xFFFFU)
#define DSPI_TXFRn_TXCMD_SHIFT    (0U)
#define DSPI_TXFRn_TXCMD(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TXCMD_SHIFT)) & DSPI_TXCMD_MASK)

#define DSPI_TXFRn_TXDATA_MASK    (0xFFFF0000U)
#define DSPI_TXFRn_TXDATA_SHIFT    (16U)
#define DSPI_TXFRn_TXDATA(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TXDATA_SHIFT)) & DSPI_TXDATA_MASK)

/* RXFRn */
#define DSPI_RXFRn_RXDATA_MASK    (0xFFFF0000U)
#define DSPI_RXFRn_RXDATA_SHIFT    (16U)
#define DSPI_RXFRn_RXDATA(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_RXDATA_SHIFT)) & DSPI_RXDATA_MASK)

/* DSICR */
#define DSPI_DSICR_TXSS_MASK    (0x1000U)
#define DSPI_DSICR_TXSS_SHIFT    (12U)
#define DSPI_DSICR_TXSS(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_TXSS_SHIFT)) & DSPI_TXSS_MASK)

#define DSPI_DSICR_CID_MASK    (0x8000U)
#define DSPI_DSICR_CID_SHIFT    (15U)
#define DSPI_DSICR_CID(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_CID_SHIFT)) & DSPI_CID_MASK)

#define DSPI_DSICR_DCONT_MASK    (0x10000U)
#define DSPI_DSICR_DCONT_SHIFT    (16U)
#define DSPI_DSICR_DCONT(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DCONT_SHIFT)) & DSPI_DCONT_MASK)

#define DSPI_DSICR_DSICTAS_MASK    (0xE0000U)
#define DSPI_DSICR_DSICTAS_SHIFT    (17U)
#define DSPI_DSICR_DSICTAS(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DSICTAS_SHIFT)) & DSPI_DSICTAS_MASK)

#define DSPI_DSICR_DPCS5_MASK    (0x4000000U)
#define DSPI_DSICR_DPCS5_SHIFT    (26U)
#define DSPI_DSICR_DPCS5(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DPCS5_SHIFT)) & DSPI_DPCS5_MASK)

#define DSPI_DSICR_DPCS4_MASK    (0x8000000U)
#define DSPI_DSICR_DPCS4_SHIFT    (27U)
#define DSPI_DSICR_DPCS4(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DPCS4_SHIFT)) & DSPI_DPCS4_MASK)

#define DSPI_DSICR_DPCS3_MASK    (0x10000000U)
#define DSPI_DSICR_DPCS3_SHIFT    (28U)
#define DSPI_DSICR_DPCS3(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DPCS3_SHIFT)) & DSPI_DPCS3_MASK)

#define DSPI_DSICR_DPCS2_MASK    (0x20000000U)
#define DSPI_DSICR_DPCS2_SHIFT    (29U)
#define DSPI_DSICR_DPCS2(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DPCS2_SHIFT)) & DSPI_DPCS2_MASK)

#define DSPI_DSICR_DPCS1_MASK    (0x40000000U)
#define DSPI_DSICR_DPCS1_SHIFT    (30U)
#define DSPI_DSICR_DPCS1(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DPCS1_SHIFT)) & DSPI_DPCS1_MASK)

#define DSPI_DSICR_DPCS0_MASK    (0x80000000U)
#define DSPI_DSICR_DPCS0_SHIFT    (31U)
#define DSPI_DSICR_DPCS0(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DPCS0_SHIFT)) & DSPI_DPCS0_MASK)

/* SDR */
#define DSPI_SDR_SER_DATA_MASK    (0xFFFF0000U)
#define DSPI_SDR_SER_DATA_SHIFT    (16U)
#define DSPI_SDR_SER_DATA(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_SER_DATA_SHIFT)) & DSPI_SER_DATA_MASK)

/* ASDR */
#define DSPI_ASDR_ASER_DATA_MASK    (0xFFFF0000U)
#define DSPI_ASDR_ASER_DATA_SHIFT    (16U)
#define DSPI_ASDR_ASER_DATA(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_ASER_DATA_SHIFT)) & DSPI_ASER_DATA_MASK)

/* COMPR */
#define DSPI_COMPR_ASER_DATA_MASK    (0xFFFF0000U)
#define DSPI_COMPR_ASER_DATA_SHIFT    (16U)
#define DSPI_COMPR_ASER_DATA(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_ASER_DATA_SHIFT)) & DSPI_ASER_DATA_MASK)

/* DDR */
#define DSPI_DDR_DESER_DATA_MASK    (0xFFFF0000U)
#define DSPI_DDR_DESER_DATA_SHIFT    (16U)
#define DSPI_DDR_DESER_DATA(x)    (((uint32_t)(((uint32_t)(x)) << DSPI_DESER_DATA_SHIFT)) & DSPI_DESER_DATA_MASK)

