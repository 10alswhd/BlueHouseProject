/*!
*******************************************************************************
* \File: ddrCalibrationAlgos.c
* \Definition:  Calibration of read delas, write delays , calibration of gaters
*******************************************************************************
* Description: Calibration includes :
* Write calibration in Single mode
* Read calibration in single mode
* Gater calibration in differential mode
* Write / Read calibration in differential mode
*
* \date 30/07/2012
* \author laitassou
* \version %version: 0 %
*
*******************************************************************************
* <b>MODIFICATION HISTORY :</b>
* \li (type) - date - author - description
*******************************************************************************
**/

#include "ddrHALCalibration.h"
#include "ddrCalibrationHelper.h"
#include "embeddedGpUtils.h"



#ifdef __cplusplus
extern "C" {
#endif


// PREF to use = "drc" for  ddr calibrate



/*
 * common types
 */

typedef enum
{
	BYTE_0 = 0,
	BYTE_1,
	BYTE_2,
	BYTE_3,
	ALL_BYTE
} drcBYTE_NUMBER;

typedef enum 
{
   SINGLEENDED_IO = 0 ,
   DIFF_IO,
   SINGLE_DIFF_MODE_MAX
}  drcSINGLE_DIFF_MODE;   


typedef enum
{
	TYPICAL_CHECK 	= 0, 
	AGRESSIVE_CHECK,			
	CHECK_MODE_MAX
} drcCHECK_MODE;  


 
/*
 //
 //  types for Gaters calibration
 */ 
 
 
 /*
 //
 // for drawing
 */
 extern pdrcDrawWindow drcDrawBuffer;
 /*
 // variables to store Target Windows
 //
 */

 //pDdrWindow pReadWindow ; defined before like this
drcDDR_WINDOW pReadWindow []= 
{
	{0, 255, 128, ebd_false, 0, TARGET_READ_WINDOW},  // byte 0 
	{0, 255, 128, ebd_false, 1, TARGET_READ_WINDOW},  // byte 1
	{0, 255, 128, ebd_false, 2, TARGET_READ_WINDOW},  // byte 2
	{0, 255, 128, ebd_false, 3, TARGET_READ_WINDOW}   // byte 3
};

// pDdrWindow pWriteWindow ;defined before like this
drcDDR_WINDOW pWriteWindow [] = 
{
	{0,255,128,ebd_false, 0, TARGET_WRITE_WINDOW}
};
  
ebd_uint8_t drcZeroPointDelayU8 = 0;

 /**
 // variables to store gaters calibration info
 //
 */

 ebd_uint8_t drcDelays [4] = {0,0,0,0};
 ebd_bool_t  drcDelayStatus [4] = {ebd_false, ebd_false, ebd_false, ebd_false};
 
 ebd_uint8_t  drcDigCycle = 0;
 ebd_uint8_t  drcDigQtr = 0; 
 
 
 // constants & defines
 
/**
 * Default value to check window validity, this value would be increased after first tests to 
 * some big value (120)
 * to be more accurate the ideal criterion should be expresssed in some low ( gaussian) where 
 * values should be big near the center and as small as we are far from the center
 */
#define drcVALID_CRITERION    (30) 



/**
 * Default constant to use during Write windows search
 */
#define   drcALL_BYTES        (0xff)


/**
 * Constant to use in order to capture more informations for any given axis point:
 * For a given (read point) search all write points that works instead of stoping when one
 * working point is found
 */
//#define drcENHANCED_ALGO_CAPTURE  



/**
 * Open points :
 * 1)
 * Algorithms can be enhanced by using dichotomy: instead of sweeping all value during Target Search
 * we can start from the theoric center (128) and go abroad the area by dichotomy.
 *
 *2) 
 * During  Window search it is possible to have one point  in the middle  of write or read axis that doesn't
 * belong to any Target Window => this will result in two separate diagramms
 * if this occurs it should be a hardware problem
 * but algortihms will be upgraded to select the best diagramm.
 *
 */

 


/* --------------------------------------------------------------------------------
// read / write calibration
// Goal : find center of window , for read and for write
//  --------------------------------------------------------------------------------
*/


/* --------------------------------------------------------------------------------
 * Config Memory to desired mode using LMR (Load Mode Register) command ( EMRS(1) )
 * @paramter Pmode -> drcSINGLE_DIFF_MODE  : { SINGLEENDED_IO, DIFF_IO}
 * SINGLEENDED_IO for single ended either for IOs or for Memory
 * DIFF_IO for differential mode either for IOs or for Memory
 * Diff or signle ended means using DQS/_DQS or DQS only , this is managed by
 * A10 field in MRS mode
 * SINGLE / DIFF mode is programmed using EMRS(1) mode
 * --------------------------------------------------------------------------------
 */
static void drcDdrConfigMemoryMode(drcSINGLE_DIFF_MODE Pmode)
{	
    ebd_uint32_t  esdcrRegValueU32 = 0;

	esdcrRegValueU32 |=  (0x1<<ESDSCR_CON_REQ_SHIFT) ; // command request
	esdcrRegValueU32 |=  (0x0<<ESDSCR_CMD_SHIFT) ; // No command
	
	GET_ESDCTL_REGS()->ESDSCR = esdcrRegValueU32; // con_req call
	while ( ~ ((GET_ESDCTL_REGS()->ESDSCR) & (ESDSCR_CON_ACK_MASK<<ESDSCR_CON_ACK_SHIFT) ) );  // Wait ack	
	
	esdcrRegValueU32 |=  (0x1<<ESDSCR_BA_SHIFT) ; // BA[1:0] =2'b01 for EMRS(1) mode
	esdcrRegValueU32 |=  (0x3<<ESDSCR_CMD_SHIFT) ; // Load mode reg command
	esdcrRegValueU32 |=  (0x0<<SDSCR_PSEUDO_ADDR_SHIFT) ; // prepare pseudo address
	
	switch(Pmode)
	{
		case SINGLEENDED_IO:
			esdcrRegValueU32 |=  (0x4040<<SDSCR_PSEUDO_ADDR_SHIFT) ; // prepare pseudo address with SINGLE DQS
		break;
		
		case DIFF_IO:
			esdcrRegValueU32 |=  (0x40<<SDSCR_PSEUDO_ADDR_SHIFT) ; // prepare pseudo address iwth Diff DQS
		break;
		
		default:
		break;
	}	
	
	GET_ESDCTL_REGS()->ESDSCR = esdcrRegValueU32; // set register
	return;	
}

/* --------------------------------------------------------------------------------
 * Set DQS mode in ESDC 
 * @paramter Pmode -> drcSINGLE_DIFF_MODE  : { SINGLEENDED_IO, DIFF_IO}
 * --------------------------------------------------------------------------------
 */
static void drcDdrControllerConfigMode( drcSINGLE_DIFF_MODE Pmode)
{	
	ebd_uint32_t	esdmiscRegValueU32 = GET_ESDCTL_REGS()->ESDMISC;
	
	switch(Pmode)
	{
		case SINGLEENDED_IO:
			esdmiscRegValueU32 &= ~(ESDMISC_DIFF_DQS_EN_MASK << ESDMISC_DIFF_DQS_EN_SHIFT);
		break;
		
		case DIFF_IO:
			esdmiscRegValueU32 |= (ESDMISC_DIFF_DQS_EN_MASK << ESDMISC_DIFF_DQS_EN_SHIFT);
		break;
		
		default:
		break;
	}	
	GET_ESDCTL_REGS()->ESDMISC = esdmiscRegValueU32;
	return;
}


/* --------------------------------------------------------------------------------
 * Config DQS/_DQS Ios pull-up pull-down
 * @paramter Pmode -> drcSINGLE_DIFF_MODE  : { SINGLEENDED_IO, DIFF_IO}
 * Add pull up/ pull down in case of single ended mode 
 * Remove them else
 * Config is done in MUXIO bloc
 * --------------------------------------------------------------------------------
 */
static void drcIOMuxCConfig(drcSINGLE_DIFF_MODE Pmode)
{
		
	switch(Pmode)
	{
		case SINGLEENDED_IO: // enable pull/keeper
			GET_IOMUXC_DQS_REGS()->IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS0  |= ( PAD_SDQS_PKE_MASK << PAD_SDQS_PKE_SHIFT);
			GET_IOMUXC_DQS_REGS()->IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS1  |= ( PAD_SDQS_PKE_MASK << PAD_SDQS_PKE_SHIFT);
			GET_IOMUXC_DQS_REGS()->IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS2  |= ( PAD_SDQS_PKE_MASK << PAD_SDQS_PKE_SHIFT);
			GET_IOMUXC_DQS_REGS()->IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS3  |= ( PAD_SDQS_PKE_MASK << PAD_SDQS_PKE_SHIFT);
			break;
		
		case DIFF_IO:  // disable pull/keeper
			GET_IOMUXC_DQS_REGS()->IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS0  &= ~( PAD_SDQS_PKE_MASK << PAD_SDQS_PKE_SHIFT);
			GET_IOMUXC_DQS_REGS()->IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS1  &= ~( PAD_SDQS_PKE_MASK << PAD_SDQS_PKE_SHIFT);
			GET_IOMUXC_DQS_REGS()->IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS2  &= ~( PAD_SDQS_PKE_MASK << PAD_SDQS_PKE_SHIFT);
			GET_IOMUXC_DQS_REGS()->IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS3  &= ~( PAD_SDQS_PKE_MASK << PAD_SDQS_PKE_SHIFT);		
		break;
		
		default:			
		break;
	}	
	
	return;
}


/* --------------------------------------------------------------------------------
 * Enable or disable calibration cells , 
 * @paramter : PenableB -> boolean 
 * when activated calibration cells perform continuous measurments
 * Set all delay registers in calibration mode by clearing SEL_DLY fields
 * --------------------------------------------------------------------------------
 */
static void drcDdrConfigCalib ( ebd_bool_t PenableB,ebd_uint8_t PwhichRegisterU8)
{
	ebd_uint32_t esddlyRegValueU32;
	
	if( PwhichRegisterU8 == 0)
	{
		esddlyRegValueU32 = GET_ESDCTL_REGS()->ESDDLY1;
	}
	else if( PwhichRegisterU8 == 1)
	{
		esddlyRegValueU32 = GET_ESDCTL_REGS()->ESDDLY2;
	}
	else if( PwhichRegisterU8 == 2)
	{
		esddlyRegValueU32 = GET_ESDCTL_REGS()->ESDDLY3;
	}
	else if( PwhichRegisterU8 == 3)
	{
		esddlyRegValueU32 = GET_ESDCTL_REGS()->ESDDLY4;
	}
	else if (PwhichRegisterU8 == 4)
	{
		esddlyRegValueU32 = GET_ESDCTL_REGS()->ESDDLY5;
	}
	else
	{
	    DbgPrintf("Error in config calibration registers\n");
		return;
		//exit(ERROR);
	}
		
	if( PenableB == ebd_true)
	{
		esddlyRegValueU32 &= ~ (ESDDLY_R_SEL_DLY_REG_MASK << ESDDLY_R_SEL_DLY_REG_SHIFT);
	}
	else
	{
		esddlyRegValueU32 |= (ESDDLY_R_SEL_DLY_REG_MASK << ESDDLY_R_SEL_DLY_REG_SHIFT);
	}
	
	if( PwhichRegisterU8 == 0)
	{
		GET_ESDCTL_REGS()->ESDDLY1 = esddlyRegValueU32 ;
	}
	else if( PwhichRegisterU8 == 1)
	{
		GET_ESDCTL_REGS()->ESDDLY2 = esddlyRegValueU32;
	}
	else if( PwhichRegisterU8 == 2)
	{
		GET_ESDCTL_REGS()->ESDDLY3 = esddlyRegValueU32;
	}
	else if( PwhichRegisterU8 == 3)
	{
		GET_ESDCTL_REGS()->ESDDLY4 = esddlyRegValueU32;
	}
	else if (PwhichRegisterU8 == 4)
	{
		GET_ESDCTL_REGS()->ESDDLY5 = esddlyRegValueU32;
	}
	else
	{
	    DbgPrintf("Error during regs configuration\n");		
	}
	
	return;
}



/* --------------------------------------------------------------------------------
 * Read total delay in register ESDGPR
 * decrease abs_delay_offset5 until total delay reach zero
 * method can be enhanced : {use some dichotomic insead of sweeping all values
 * --------------------------------------------------------------------------------
 */
static ebd_uint8_t drcDdrSearchZeroPoint(void)
{
	ebd_uint8_t cnt;
	
	GET_ESDCTL_REGS()->ESDDLY5 |= (ESDDLY_R_DLY_ABS_OFFSET_MASK << ESDDLY_R_DLY_ABS_OFFSET_SHIFT); // init abs_offset to 255

	while ((GET_ESDCTL_REGS()->ESDGPR)& ESDGPR_QTR_CYCLE_LENGTH_MASK)
	{
	   GET_ESDCTL_REGS()->ESDDLY5 -= 1;
	   
	   // need to introduce some delay here ??
	   //__nop();  // call ARM nop instruction  can be used to insert delay
	   //__nop();  // but its objective is to avoid that compiler inverses some instructions
	   //__nop();
	   for( cnt = 50; cnt > 0; cnt--)
	   {}	   
	   
	}
	drcZeroPointDelayU8 = (ebd_uint8_t)( ((GET_ESDCTL_REGS()->ESDGPR)& ESDGPR_QTR_CYCLE_LENGTH_MASK) >> ESDDLY_R_DLY_ABS_OFFSET_SHIFT);	
	DbgPrintf("Found zero point %d\n",drcZeroPointDelayU8);
	
	return  drcZeroPointDelayU8 ;
}


/* --------------------------------------------------------------------------------
 *  Set delay in Delay registers : write PdelayAbsOffsetU8 in  ESDDLY_R_DLY_ABS_OFFSET fields
 *  @paramters :
 *     Pmode      => TargetWindow
 *     PwhichByteU8 => Byte lane for Read window
 *     tmpDely   => applied delay to dly_abs_offset field
 * --------------------------------------------------------------------------------
 */
 static void  drcSetDelayInRegister(drcTARGET_RW_MODE Pmode, ebd_uint8_t PwhichByteU8, ebd_uint8_t PdelayAbsOffsetU8)
 {
	if(Pmode == TARGET_READ_WINDOW)
	{
		if(PwhichByteU8 == 0)
		{
			GET_ESDCTL_REGS()->ESDDLY1  &=  ~(ESDDLY_R_DLY_ABS_OFFSET_MASK << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
			GET_ESDCTL_REGS()->ESDDLY1  |= (PdelayAbsOffsetU8 << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
		}
		else if(PwhichByteU8 == 1)
		{
			GET_ESDCTL_REGS()->ESDDLY2  &=  ~(ESDDLY_R_DLY_ABS_OFFSET_MASK << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);	
			GET_ESDCTL_REGS()->ESDDLY2  |= (PdelayAbsOffsetU8 << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
		}
		else if(PwhichByteU8 == 2)
		{
			GET_ESDCTL_REGS()->ESDDLY3  &=  ~(ESDDLY_R_DLY_ABS_OFFSET_MASK << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
			GET_ESDCTL_REGS()->ESDDLY3  |= (PdelayAbsOffsetU8 << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
		}
		else if(PwhichByteU8 == 3)
		{
			GET_ESDCTL_REGS()->ESDDLY4  &=  ~(ESDDLY_R_DLY_ABS_OFFSET_MASK << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
			GET_ESDCTL_REGS()->ESDDLY4  |= (PdelayAbsOffsetU8 << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
		}
		else if(PwhichByteU8 == 3)
		{
			GET_ESDCTL_REGS()->ESDDLY4  &=  ~(ESDDLY_R_DLY_ABS_OFFSET_MASK << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
			GET_ESDCTL_REGS()->ESDDLY4  |= (PdelayAbsOffsetU8 << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
		}
		else
		{
			DbgPrintf(" Not valid delay register \n");
			return;
			//exit(ERROR);
		}
	}else  if(Pmode == TARGET_WRITE_WINDOW)
	{
		GET_ESDCTL_REGS()->ESDDLY5  &=  ~(ESDDLY_R_DLY_ABS_OFFSET_MASK << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
		GET_ESDCTL_REGS()->ESDDLY5  |= (PdelayAbsOffsetU8 << ESDDLY_R_DLY_ABS_OFFSET_SHIFT);
	}
	else
	{
	
	}
	
	return;
}


/* --------------------------------------------------------------------------------
 * compute center for given ddrWindow and update structs data
 * data is then used to update reggisters
 * @paramters 
 * --------------------------------------------------------------------------------
 */
static void drcUpdateWindowsCenters( drcTARGET_RW_MODE Pmode, ebd_uint8_t PwhichByteU8)
{

	if(Pmode >= TARGET_WINDOW_MAX)	
	{
		DbgPrintf("Paramter Error mode during Target window Valid\n");
		return;
		//exit(ERROR);
	}		
	if(Pmode == TARGET_READ_WINDOW)
	{
		(pReadWindow+PwhichByteU8)->centerU8 = (ebd_uint8_t) (( (pReadWindow+PwhichByteU8)->minU8 + (pReadWindow+PwhichByteU8)->maxU8 ) /2 );
	}
	else if (Pmode == TARGET_WRITE_WINDOW)
	{
		pWriteWindow->centerU8 = (ebd_uint8_t) ((pWriteWindow->minU8 + pWriteWindow->maxU8) /2 );
	}
	
	return;
	
}


/* --------------------------------------------------------------------------------
 * Check function that calls tests from the DDR testers, this should include tests 
 * @paramters :
 *	pWindow -> pointer to struct
 *  mCheck  -> check type : TYPICAL_CHECK for Target Window Search and aggressive for True window
 * Call here functions from DDR tester
 * --------------------------------------------
 * Principle of this function :
 * --------------------------------------------
 * How the data is written into the DRAM before the calibration as this also relies on a 
 * data-strobe-to-data-offset relationship.
 * This data writing is simply accomplished by using static data (e.g., no edges, 
 * all data is held to the same value for the entire burst length) with small burst lengths. 
 * A longer burst length is then used during the reads
 *
 * --------------------------------------------------------------------------------
 */ 
 static ebd_bool_t DdrCheck(pDdrWindow pWindow,ebd_uint8_t ByteLane, drcCHECK_MODE mCheck)
 {
 }
 


/* --------------------------------------------------------------------------------
 *  Search Target window : Target window is a consecutive valid points using a step of 5
 *  algo : use a step of 5 to sweep all points, for each point check that exists at least
 *  one point where check data is ok 
 * --------------------------------------------------------------------------------
 */
static void DdrSearchTargetWindow(drcTARGET_RW_MODE Pmode,ebd_uint8_t PwhichByteU8)
{
	ebd_uint32_t tmpDely = 0;
	ebd_uint32_t i,j;
	ebd_bool_t status = ebd_false;
	ebd_uint8_t cnt = 0;
	
	ebd_bool_t gblStatus = ebd_false;	// for enhanced mode (log windows for any read points)
	
	static ebd_bool_t minfound = ebd_false;
	
	if(Pmode >= TARGET_WINDOW_MAX)	
	{
		DbgPrintf("Parameter Error mode during Target window Search\n");
		return;
		//exit(ERROR);
	}
	
	tmpDely  = drcZeroPointDelayU8 ;
	
	if(Pmode == TARGET_READ_WINDOW)
	{
		DbgPrintf("Start search Target Read Window for byte :%d\n",PwhichByteU8);
		
		// init Target window minU8 to drcZeroPointDelayU8;		
		(pReadWindow+PwhichByteU8)->minU8 = tmpDely;
		drcSetDelayInRegister(TARGET_READ_WINDOW,PwhichByteU8,tmpDely);
		
        pWriteWindow->minU8 = tmpDely;
		drcSetDelayInRegister(TARGET_WRITE_WINDOW,-1,tmpDely);
			

		for (i=drcZeroPointDelayU8; i<= 255; i=i+drcSEARCH_WINDOW_STEP)
		{	
			drcSetDelayInRegister(TARGET_READ_WINDOW,PwhichByteU8,tmpDely);
		
			while(~gblStatus && (tmpDely <=255))
			{
				status = DdrCheck(pReadWindow,PwhichByteU8,TYPICAL_CHECK);	
				
			    #if defined (drcENHANCED_ALGO_CAPTURE)
				gblStatus & = status ;
				#else
				gblStatus = status ; 
				#endif
				
				if(status == ebd_false) 
				{
					#if defined (drcENHANCED_ALGO_CAPTURE)
					if(minfound == ebd_true) // found point not ok where one good point was found before
					{
						if(tmpDely - ((drcDrawBuffer+ i - drcZeroPointDelayU8)->wPointMinU8) >= drcVALID_CRITERION)
						{
							gblStatus = ebd_true; // stop search
						}
						else
						{
							// update min point because one erroneus point in the area
							minfound = ebd_false;
						}
					}
					#endif
					tmpDely++;
					drcSetDelayInRegister(TARGET_WRITE_WINDOW,-1,tmpDely);	
				}
				else
				{
					
					// here add mode where we want to capture all windows validity for any given point i
					// Described algorithm doesn't use this , but in order to get all information it is recommended
					// to do that
					#if defined (drcENHANCED_ALGO_CAPTURE)
					if(~minfound)
					{
						// update struct pWritedWindow
						pReadWindow+PwhichByteU8)->minU8 = i;
						
						// fill buffer for drawing
						(drcDrawBuffer+ i - drcZeroPointDelayU8)->rPointU8 = i;							
						(drcDrawBuffer+ i - drcZeroPointDelayU8)->wPointMinU8 = tmpDely;
						(drcDrawBuffer+ i - drcZeroPointDelayU8)->windowNumerU8 = PwhichByteU8 ;
							
						minfound = ebd_true;
					}
					else
					{
						// update max
						(drcDrawBuffer+ i - drcZeroPointDelayU8)->wPointMaxU8 = tmpDely;							
					}
					#else
					
					// point  ( i,tmpDely) inside Window
					if(~minfound)	
					{
						(pReadWindow+PwhichByteU8)->minU8 = i; 	// update struct pWritedWindow	
					}
					else
					{
						(pReadWindow+PwhichByteU8)->maxU8 = i; 
					}				
					
					#endif
				}
			}
					
		}			
	}
	else if(Pmode == TARGET_WRITE_WINDOW)
	{
		DbgPrintf("Start search Target Write Window for all bytes \n");		

		// update Read windows in ESDC read delay registers
		for(j = 0; j <=3 ; j++)
		{
			drcUpdateWindowsCenters(TARGET_READ_WINDOW,j);
			tmpDely =  (pReadWindow+j)->centerU8;
			drcSetDelayInRegister(TARGET_READ_WINDOW,j,tmpDely);
		}
		
		// TODO add some tempo here  : DONE
		for(cnt =50 ; cnt > 0 ; cnt --)
		{}
		
		// write target window	
		for (i=drcZeroPointDelayU8; i<= 255; i=i+drcSEARCH_WINDOW_STEP)
		{	
			drcSetDelayInRegister(TARGET_WRITE_WINDOW,-1,i);
			
			status = DdrCheck(pWriteWindow,drcALL_BYTES,TYPICAL_CHECK);	
			
			#if defined (drcENHANCED_ALGO_CAPTURE)
			gblStatus & = status ;
			#else
			gblStatus = status ; 
			#endif
			
			if (status == ebd_true) // Axis  ( i) inside Write Window
			{
				DbgPrintf( "Point %d  is inside Write area\n",i);	
				if(~minfound)	
				{
					pWriteWindow->minU8 = i; 	// update struct pWritedWindow	
				}
				else
				{
					pWriteWindow->maxU8 = i;
				}
			}
			else
			{
				DbgPrintf( "Write area search is not yet found or exceeded at point %d\n",i);	
			}						
		}			
					
	}
	
	return;
 }
 
 
 
/* --------------------------------------------------------------------------------
 * Search Target window : Target window is a consecutive valid points usin a step of 5
 * algo : use a step of 1 to sweep all points, for each point check that exists at least
 * one point where check data is ok.
 * data check use aggressive method to permit a global certified check
 * --------------------------------------------------------------------------------
 */
static void DdrSearchTrueWindow(drcTARGET_RW_MODE Pmode,ebd_uint8_t PwhichByteU8)
{
	ebd_uint8_t tmpDely = 0;
	ebd_uint8_t i = 0;
	ebd_bool_t status = ebd_false;
	ebd_uint8_t min, max;
	
	if(Pmode >= TARGET_WINDOW_MAX)	
	{
		DbgPrintf("Parameter Error mode during Target window Search\n");
		return;
		//exit(ERROR);
	}	

	if(Pmode == TARGET_READ_WINDOW)
	{
		DbgPrintf("Start search True Read Window for byte :%d\n",PwhichByteU8);
		
		// update register dly5 to center of write window;		
		tmpDely = pWriteWindow->centerU8;
		drcSetDelayInRegister(TARGET_WRITE_WINDOW,-1,tmpDely);	
		
		min = (pReadWindow+PwhichByteU8)->minU8 ;
		max = (pReadWindow+PwhichByteU8)->maxU8 ;
		
		// avoid overloads
		//min = (min>=4) ? (min-4) : 0;
		if(min >=4 )
		{
			min -=4;
		}
		else
		{
		  min = 0;
		}
		// max = (max <=251) ? (max+4):0xff;
		if(max<=251)
		{
			max +=4;
		}
		else
		{
			max = 255;
		}		
		
		for (i=min; i<= max; i=i+1)
		{	
			drcSetDelayInRegister(TARGET_READ_WINDOW,PwhichByteU8,i);
			status = DdrCheck(pReadWindow,PwhichByteU8,AGRESSIVE_CHECK);
			
			if (status == ebd_true)
			{
				DbgPrintf( "point %d inside true Read window for byte %d\n",i,PwhichByteU8);
				 
				(pReadWindow+PwhichByteU8)->maxU8 = i; // good enough in case of continuous points
			}
			else
			{
				(pReadWindow+PwhichByteU8)->minU8 = i;
				DbgPrintf( "point %d is outside True Read Window for byte %d\n",i,PwhichByteU8);
			}						
		}			
	}
	else if(Pmode == TARGET_WRITE_WINDOW)
	{
		DbgPrintf("Start search True Write Window %d\n");
		
		min = (pWriteWindow)->minU8 ;
		max = (pWriteWindow)->maxU8 ;
		
		// avoid overloads
		//min = (min>=4) ? (min-4) : 0;
		if(min >=4 )
		{
			min -=4;
		}
		else
		{
		  min = 0;
		}
		// max = (max <=251) ? (max+4):0xff;
		if(max<=251)
		{
			max +=4;
		}
		else
		{
			max = 255;
		}		
		
		// true write window	
		for (i=min; i<= max; i=i+1)
		{	
			drcSetDelayInRegister(TARGET_WRITE_WINDOW,-1,i);
			
			status = DdrCheck(pWriteWindow,drcALL_BYTES,AGRESSIVE_CHECK);	
			
			if (status == ebd_true)
			{
				DbgPrintf( "point %d inside true Write window \n",i);
				 
				(pWriteWindow)->maxU8 = i; // good enough in case of continuous points
			}
			else
			{
				(pWriteWindow)->minU8 = i;
				DbgPrintf( "point %d is outside True Write Window for byte %d\n",i);
			}							
		}			
					
	}
	
	return;
 }
 
/* --------------------------------------------------------------------------------
 * Check whether given window is valid and update its status  
 * @paramter : pDdrWindow  
 * --------------------------------------------------------------------------------
 */
 static ebd_bool_t DdrTargetWindowValid (pDdrWindow PwindowP)
 {
    ebd_uint8_t gap = 0;
    ebd_bool_t status ;
	
	if(PwindowP->windowMode >= TARGET_WINDOW_MAX)	
	{
		DbgPrintf("Paramter Error mode during Target window Valid\n");
		return ebd_false;
		//exit(ERROR);
	}
	
	status = (PwindowP->minU8 < PwindowP->maxU8) && (PwindowP->maxU8 - PwindowP->minU8 > drcVALID_CRITERION);
	gap = PwindowP->maxU8 - PwindowP->minU8;
	PwindowP->validB = status;
	
	if(status == ebd_true)
	{
		if(PwindowP->windowMode == TARGET_WRITE_WINDOW)
		{
			DbgPrintf("WRITE Window is valid  and its width : %d\n", gap);
		}
		else if(PwindowP->windowMode == TARGET_READ_WINDOW )
		{
			DbgPrintf("READ Window %d is valid  and its width : %d\n",PwindowP->windowNumerU8 , gap);		
		}

	}
	else
	{
		if(PwindowP->windowMode == TARGET_WRITE_WINDOW)
		{
			DbgPrintf("WRITE Window is not valid  and its width : %d\n", gap);
		}
		else if(PwindowP->windowMode == TARGET_READ_WINDOW )
		{
			DbgPrintf("READ Window %d is not valid  and its width : %d\n",PwindowP->windowNumerU8 , gap);		
		}
	}
	return status;  
 }
 
 

 /* --------------------------------------------------------------------------------
  * function to call for Write calibration
  * @parameter Pmode should be used for calibration in single ended or differential mode
  * --------------------------------------------------------------------------------
  */
  
 ebd_bool_t drcDdrAlgoCalibrateWrite(drcSINGLE_DIFF_MODE Pmode)
 {
	ebd_uint8_t j = 0;
	ebd_uint8_t zeropoint =0;
	ebd_bool_t status = ebd_false;
	ebd_bool_t memStatus = ebd_false;
	
	
	// config Ios, Controller, Memory 
	drcDdrConfigMemoryMode(Pmode);
	drcDdrControllerConfigMode(Pmode);
		
	drcIOMuxCConfig(Pmode);
	
	for(j=0; j<5; j++)
	{
		drcDdrConfigCalib(ebd_true,j);
	}
	
	// start algo
	
	zeropoint = drcDdrSearchZeroPoint();
	for(j=0; j<4; j++)
	{
	
		// allocate memory for drcDrawBuffer
		#if defined (drcENHANCED_ALGO_CAPTURE)
		memStatus = drcAllocateMemory();
		if(memStatus == ebd_false)
		{
			// Error mem allcoation
			return;
		}
		#endif
		
		DdrSearchTargetWindow(TARGET_READ_WINDOW,j);
		
		
		// draw diagram ofr byte j
		#if defined (drcENHANCED_ALGO_CAPTURE)
		drcDrawDiagram();
		#endif
		
		drcUpdateWindowsCenters(TARGET_READ_WINDOW,j);
		
		status = DdrTargetWindowValid((pReadWindow+j));	
		
		#if defined (drcENHANCED_ALGO_CAPTURE)
		drcFree();
		#endif	

	}
	
	DdrSearchTargetWindow(TARGET_WRITE_WINDOW,-1);
	status = DdrTargetWindowValid((pWriteWindow));

	DdrSearchTrueWindow(TARGET_WRITE_WINDOW, -1);	
	status = DdrTargetWindowValid(pWriteWindow);

	drcUpdateWindowsCenters(TARGET_WRITE_WINDOW, -1);

	return status;	
 }
 
 /* --------------------------------------------------------------------------------
  * function to call for read calibration
  * @parameter Pmode should be used for calibration in single ended or differential mode
  * --------------------------------------------------------------------------------
  */
 ebd_bool_t drcDdrAlgoCalibrateRead(drcSINGLE_DIFF_MODE Pmode)
 {
	ebd_bool_t status = ebd_false;
	ebd_uint8_t j = 0;

	
	// config Ios, Controller, Memory 
	drcDdrConfigMemoryMode(Pmode);
	drcDdrControllerConfigMode(Pmode);
		
	drcIOMuxCConfig(Pmode);
	for(j=0; j<5; j++)
	{
		drcDdrConfigCalib(ebd_true,j);
	}
	
	// start algo	
	for(j=0; j<4; j++)
	{
		DdrSearchTrueWindow(TARGET_READ_WINDOW,j);
		drcUpdateWindowsCenters(TARGET_READ_WINDOW,j);		
		status = DdrTargetWindowValid((pReadWindow+j));	
	}	
	
	return status;
 }
 
 
  
/* --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// Gaters calibration
// Results is to find delays
//--------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
*/


/* --------------------------------------------------------------------------------
 * Enable or disable gating of DQS in
 * @parameter : Penable 
 * --------------------------------------------------------------------------------
 */
static void drcDdrSetGating(ebd_bool_t Penable)
{
	ebd_uint32_t gprRegValue = 0;
	
	gprRegValue = GET_ESDCTL_REGS()->ESDGPR;
	
	if( Penable == ebd_true)
	{
		gprRegValue |=  (ESDGPR_DIG_EN_MASK << ESDGPR_DIG_EN_SHIFT);
	}
	else
	{
		gprRegValue &=  ~(ESDGPR_DIG_EN_MASK << ESDGPR_DIG_EN_SHIFT);
	}
	
	 GET_ESDCTL_REGS()->ESDGPR = gprRegValue;
	 
	 return;	
}
  
  
/* --------------------------------------------------------------------------------
 * update delay fields of ESDCGPR register  with new delay values
 * @parameter : Pdelay pointer to delay values 
 * --------------------------------------------------------------------------------
 */
static void drcDdrGaterUpdateRegsDelays(ebd_uint8_t * Pdelay)
 {
	ebd_uint32_t delay =0;
	ebd_uint32_t esdgpr =0;
	ebd_uint32_t  i ;
	if(Pdelay == NULL)
	{
		DbgPrintf("Error pointer Null\n");
		return;
		//exit(ERROR);
	}
	// clear old delays
	esdgpr = GET_ESDCTL_REGS()->ESDGPR;
	esdgpr &= ~(ESDGPR_DIG_OFF0_MASK << ESDGPR_DIG_OFF0_SHIFT);
	esdgpr &= ~(ESDGPR_DIG_OFF1_MASK << ESDGPR_DIG_OFF1_SHIFT);
	esdgpr &= ~(ESDGPR_DIG_OFF2_MASK << ESDGPR_DIG_OFF2_SHIFT);
	esdgpr &= ~(ESDGPR_DIG_OFF3_MASK << ESDGPR_DIG_OFF3_SHIFT);
	
	for(i = 0; i <4; i++)
	{
		delay = *(Pdelay+i);
		if((delay)>3)
		{
			DbgPrintf("Delay value %d exceeds 3 \n",delay);
			return;
		}		
		
		switch(i)
		{
			case 0:
				esdgpr |= (delay<< ESDGPR_DIG_OFF0_SHIFT);
				break;
			case 1:
				esdgpr |= (delay<< ESDGPR_DIG_OFF1_SHIFT);
				break;
			case 2:
				esdgpr |= (delay<< ESDGPR_DIG_OFF2_SHIFT);
				break;
			case 3:
				esdgpr |= (delay<< ESDGPR_DIG_OFF3_SHIFT);
				break;	
			default: 				
				break;
		}		
		
	}
	
	// clear qtr and cycle delays
	esdgpr &= ~(ESDGPR_DIG_QTR_MASK << ESDGPR_DIG_QTR_SHIFT);
	esdgpr &= ~(ESDGPR_DIG_CYC_MASK << ESDGPR_DIG_CYC_SHIFT);
	
	
	esdgpr |= (drcDigCycle << ESDGPR_DIG_CYC_SHIFT );
	esdgpr |= (drcDigQtr   << ESDGPR_DIG_QTR_SHIFT );

	
	GET_ESDCTL_REGS()->ESDGPR =	esdgpr;
	
	return;
 }
 
/* --------------------------------------------------------------------------------
 * Compute new delays by stteing the common part in dedicated field 
 * @paramters:
 * Pdelay -> poniter to delays 
 * --------------------------------------------------------------------------------
 */
static void drcDdrGaterComputeNewDelays(ebd_uint8_t * Pdelay)
{
	ebd_uint8_t mindelay;
	ebd_uint8_t tmpmin1, tmpmin2;
	ebd_uint8_t dig_cyc, dig_qtr;
	
	tmpmin1  = drcMIN(*(Pdelay), *(Pdelay+1));
	tmpmin2  = drcMIN(*(Pdelay+2), *(Pdelay+3));		
	mindelay = drcMIN(tmpmin1, tmpmin2);
	
	dig_cyc  = (ebd_uint8_t) (mindelay / 4);
	dig_qtr  = (ebd_uint8_t) (mindelay % 4);
	
	
	drcDigCycle  = dig_cyc;
	drcDigQtr    = dig_qtr;
		
	*(Pdelay)   = *(Pdelay) - mindelay;
	*(Pdelay+1) = *(Pdelay+1) - mindelay;
	*(Pdelay+2) = *(Pdelay+2) - mindelay;	
	*(Pdelay+3) = *(Pdelay+3) - mindelay;
	
	 return; 
}

/* --------------------------------------------------------------------------------
 * Soft reset flushs internal FIFOs of DDR controller
 * -------------------------------------------------------------------------------- 
 */ 
static void drcControllerSoftReset()
{
	ebd_uint32_t esdmisc;
	ebd_uint32_t cnt;
	
	esdmisc = GET_ESDCTL_REGS()->ESDMISC;
	
	esdmisc &= (ESDMISC_RST_MASK<<ESDMISC_RST_SHIFT);
	
	GET_ESDCTL_REGS()->ESDMISC  = esdmisc;  // soft reset
	
	//TODO : add tempo untill memory is prepared ??	
	for(cnt=500; cnt> 0; cnt--)
	{}
}
 
 
 /* --------------------------------------------------------------------------------
  * Write patterns to memory once time, these patterns will be used to check against
  * (pattern can be saved somewhere in internal memory)
  * --------------------------------------------------------------------------------
  */
 static void drcWriteDataPattern()
 {
	//TODO
	// Call here some copy function to memory from ddr tester
	return;
 }
 
 
 /* --------------------------------------------------------------------------------
  * Check Written patterns, can check by byte or all data
  * @paramters:
  * PwhichByte : to identify which byte to test , if sett to ALL_BYTE it should test
  * all bytes 
  * --------------------------------------------------------------------------------
  */
 static ebd_bool_t drcCheckDataPattern (drcBYTE_NUMBER PwhichByte)
  {
    ebd_bool_t status;
	
	if(PwhichByte > ALL_BYTE)
	{
		DbgPrintf("Error in ddr pattern check\n");
	}	return ebd_false;
	
	//TODO
	// call here some function from ddr tester
	switch(PwhichByte)
	{
		case BYTE_0:
			break;
		case BYTE_1:
			break;
		case BYTE_2:
			break;
		case BYTE_3:
			break;
		case ALL_BYTE:
			break;
		default : 
			break;	
	}	
	
	return status;
  }
 
/* --------------------------------------------------------------------------------
 * Algo calibration: search for delay for each dqs gater, algo computes common delay
 * for gaters to minimise skew between all delays
 * Because skeaw > 3/4 means two separate read cycles
 * --------------------------------------------------------------------------------
 */
ebd_bool_t drcDdrAlgoGaters()
{
	ebd_bool_t status = ebd_false;
	ebd_uint8_t i;
	ebd_bool_t conditionExit = ebd_false;
	
	
	DbgPrintf("Start gater calibration algo \n");
		
	// config Ios, Controller, Memory 
	drcDdrConfigMemoryMode(DIFF_IO);
	drcDdrControllerConfigMode(DIFF_IO);		
	drcIOMuxCConfig(DIFF_IO);
		
	// write pattern to DDR
	drcWriteDataPattern();
	
	// init delays 
	drcDdrGaterUpdateRegsDelays(drcDelays);
	
	
	while (conditionExit == ebd_false)
	{
		for(i=0; i< 4; i++)
		{
			// Check REead
			status = drcCheckDataPattern((drcBYTE_NUMBER) (i));
			drcDelayStatus[i] = status;
		}
		// init exit condition
		conditionExit = ebd_true;		
		for(i=0; i<4; i++)
		{
			if (drcDelayStatus[i] == ebd_false)
			{
				drcDelays[i] += 1; 
				conditionExit = ebd_false;
			}			 
		}
		
		// soft reset
		drcControllerSoftReset();
		
		// compute new delays
		drcDdrGaterComputeNewDelays(drcDelays);
		
		// update registers
		drcDdrGaterUpdateRegsDelays(drcDelays);
	}
	
	// contionExit ok
	for(i=0; i<4; i++)
	{
		drcDelays[i] += 1; 
	}
	drcDdrGaterUpdateRegsDelays(drcDelays);
	
	// check all bytes
	status =  drcCheckDataPattern(ALL_BYTE);	
	
	return status;
}


// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// global verification of calibration:
// Set found delays in init ddr 
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------


/* --------------------------------------------------------------------------------
 * global function to do steps :
 * 	1) Read / write calibration in single mode
 *	2) gater calibration ( differential)
 *  3) read /write calibration in differential mode with new calibration paramters
 * --------------------------------------------------------------------------------
 */
 void drcDdrGlobalCalibrationCheck()
 {
	ebd_bool_t status = ebd_false;

	
	status = drcDdrAlgoCalibrateWrite(SINGLEENDED_IO);	
	if( status == ebd_true)
	{
		DbgPrintf("Write Calibration in SINGLE mode  succeed \n");		

	}	
	else
	{
		DbgPrintf("Write Calibration in SINGLE mode  failed \n");
	}
	
	status = drcDdrAlgoCalibrateRead(SINGLEENDED_IO);
	if( status == ebd_true)
	{
		DbgPrintf("Read Calibration in SINGLE mode  succeed \n");
	}	
	else
	{
		DbgPrintf("Read Calibration in SINGLE mode  failed \n");
	}		
	
	
	status = drcDdrAlgoGaters();
	if( status == ebd_true)
	{
		DbgPrintf("Gaters Calibration succeed \n");
	}	
	else
	{
		DbgPrintf("Read Calibration failed \n");
	}
	
	status = drcDdrAlgoCalibrateWrite(DIFF_IO);
	if( status == ebd_true)
	{
		DbgPrintf("Write Calibration in DIFFERENTIAL mode  succeed \n");
	}	
	else
	{
		DbgPrintf("Write Calibration in DIFFERENTIAL mode  failed \n");
	}
	
	status = drcDdrAlgoCalibrateRead(DIFF_IO);
 	if( status == ebd_true)
	{
		DbgPrintf("Read Calibration in DIFFERENTIAL mode  succeed \n");
	}	
	else
	{
		DbgPrintf("Read Calibration in DIFFERENTIAL mode  failed \n");
	}
	

	return;
 } 

 
 #ifdef __cplusplus
}
#endif
