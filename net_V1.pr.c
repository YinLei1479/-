/* Process model C form file: net_V1.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char net_V1_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 66A36185 66A36185 1 ray-laptop 28918 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                                         ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

#include <math.h>

/* Constant Definitions */
#define RX_IN		(0)
#define SRC_IN		(1)
#define TX_OUT		(0)
#define SINK_OUT	(1)


#define COLLECT_FINISH	(5000)
#define TIME_OUT_SIGNAL (6000)
#define INTACT_PK_SEND	(7000)

/* Transition Condition Macros */ 
#define FROM_RX_PK			(op_intrpt_type() == OPC_INTRPT_STRM) && (op_intrpt_strm () == RX_IN)
#define FROM_SRC_PK 		(op_intrpt_type() == OPC_INTRPT_STRM) && (op_intrpt_strm () == SRC_IN)

#define INTACT_START 		(op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code () == INTACT_PK_SEND)
#define COLLECT				(op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code () == COLLECT_FINISH)
#define TIME_OUT			(op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code () == TIME_OUT_SIGNAL)

/* End of Header Block */

#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(_op_last_line_passed) = __LINE__ - _op_block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(_op_last_line_passed) = 0; _op_block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
typedef struct
	{
	/* Internal state tracking for FSM */
	FSM_SYS_STATE
	/* State Variables */
	int	                    		my_address                                      ;	/* my node address */
	Objid	                  		my_id                                           ;
	Objid	                  		my_node_id                                      ;
	int	                    		type                                            ;	/* rcv pk type */
	int	                    		interactive_id                                  ;
	int	                    		to_interact_next_hop                            ;	/* the next hop to the interact node */
	int	                    		interact_pk_num                                 ;	/* the Num of the pk */
	int	                    		topo[24][24]                                    ;	/* 0 or 1 for the net topo */
	int	                    		link_interact_pk_num                            ;	/* pk num of interact collection */
	Evhandle	               		evh                                             ;	/* time out self intrpt */
	} net_V1_state;

#define my_address              		op_sv_ptr->my_address
#define my_id                   		op_sv_ptr->my_id
#define my_node_id              		op_sv_ptr->my_node_id
#define type                    		op_sv_ptr->type
#define interactive_id          		op_sv_ptr->interactive_id
#define to_interact_next_hop    		op_sv_ptr->to_interact_next_hop
#define interact_pk_num         		op_sv_ptr->interact_pk_num
#define topo                    		op_sv_ptr->topo
#define link_interact_pk_num    		op_sv_ptr->link_interact_pk_num
#define evh                     		op_sv_ptr->evh

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	net_V1_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((net_V1_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif

/*static void QWZ_rcv(Packet* pkptr)//QWZ_RCV
	{
	int nei_id;
	int nei_slot;
	int nei_in_flag;
	int two_nei_num;
	int two_nei_id[8];
	//int two_nei_in_flag;
	//int count_in;
	int i;
	
	FIN(QWZ_rcv(Packet* pkptr));
	op_pk_nfd_get (pkptr, "Address", &nei_id);
	op_pk_nfd_get (pkptr, "Slot", &nei_slot);
	nei_in_flag=0;
	if(my_neighbor[nei_id][0]==0) nei_count++;
	my_neighbor[nei_id][0]=1;
	my_neighbor[nei_id][1]=nei_slot;
	//完成邻居表与所占用时隙
	
	
	op_pk_nfd_get (pkptr, "Nei_num", &two_nei_num);
	op_pk_nfd_get (pkptr, "Nei_address_0", &two_nei_id[0]);
	op_pk_nfd_get (pkptr, "Nei_address_1", &two_nei_id[1]);
	op_pk_nfd_get (pkptr, "Nei_address_2", &two_nei_id[2]);
	op_pk_nfd_get (pkptr, "Nei_address_3", &two_nei_id[3]);
	op_pk_nfd_get (pkptr, "Nei_address_4", &two_nei_id[4]);
	op_pk_nfd_get (pkptr, "Nei_address_5", &two_nei_id[5]);
	op_pk_nfd_get (pkptr, "Nei_address_6", &two_nei_id[6]);
	op_pk_nfd_get (pkptr, "Nei_address_7", &two_nei_id[7]);
	for(i=0;i<two_nei_num;i++)
		{
		if(my_two_nei[two_nei_id[i]]==0) my_two_nei_count_sum++;
		my_two_nei[two_nei_id[i]]=1;
		}
	//完成两跳邻居节点收集
	
	now_slot_id[nei_id]=1;
	now_slot_QWZ_num++;//收集此帧中QWZ数目与发送QWZ地址
	
	FOUT;
	}
	*/
	
	
		

/* End of Function Block */

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

#if defined (__cplusplus)
extern "C" {
#endif
	void net_V1 (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_net_V1_init (int * init_block_ptr);
	void _op_net_V1_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_net_V1_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_net_V1_alloc (VosT_Obtype, int);
	void _op_net_V1_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
net_V1 (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (net_V1 ());

		{
		/* Temporary Variables */
		Packet* pkptr;
		int source;
		int i,j;
		/* End of Temporary Variables */


		FSM_ENTER ("net_V1")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "net_V1 [init enter execs]")
				FSM_PROFILE_SECTION_IN ("net_V1 [init enter execs]", state0_enter_exec)
				{
				//initial begin
				my_id = op_id_self();
				my_node_id = op_topo_parent (my_id);
				
				op_ima_obj_attr_get(my_node_id,"Address",&my_address);
				
				interactive_id=0xFF;
				to_interact_next_hop=0xFF;
				interact_pk_num=0;
				link_interact_pk_num=0;
				
				for(i=0;i<24;i++)
					for(j=0;j<24;j++) topo[i][j]=0;
				
				op_intrpt_schedule_self(op_sim_time()+200,INTACT_PK_SEND);
				printf("$$$$$$$$$$$$net over$$$$$$$$$$$$$\n");
				
				//************for test**************
				interactive_id=10;
				if(my_address==0) to_interact_next_hop=1;
				if(my_address==1) to_interact_next_hop=11;
				if(my_address==2) to_interact_next_hop=10;
				if(my_address==3) to_interact_next_hop=4;
				if(my_address==4) to_interact_next_hop=10;
				if(my_address==5) to_interact_next_hop=10;
				if(my_address==6) to_interact_next_hop=5;
				if(my_address==7) to_interact_next_hop=11;
				if(my_address==8) to_interact_next_hop=5;
				if(my_address==9) to_interact_next_hop=2;
				if(my_address==10) to_interact_next_hop=10;
				if(my_address==11) to_interact_next_hop=10;
				if(my_address==12) to_interact_next_hop=4;
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "net_V1 [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init", "idle", "tr_0", "net_V1 [init -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "net_V1 [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"net_V1")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "net_V1 [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("net_V1 [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND (FROM_RX_PK)
			FSM_TEST_COND (FROM_SRC_PK)
			FSM_TEST_COND (INTACT_START)
			FSM_TEST_COND (COLLECT || TIME_OUT)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "FROM_RX_PK", "", "idle", "rx_rcv", "tr_3", "net_V1 [idle -> rx_rcv : FROM_RX_PK / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "FROM_SRC_PK", "", "idle", "src_rcv", "tr_6", "net_V1 [idle -> src_rcv : FROM_SRC_PK / ]")
				FSM_CASE_TRANSIT (2, 4, state4_enter_exec, ;, "INTACT_START", "", "idle", "interact", "tr_8", "net_V1 [idle -> interact : INTACT_START / ]")
				FSM_CASE_TRANSIT (3, 5, state5_enter_exec, ;, "COLLECT || TIME_OUT", "", "idle", "link_state_feedback", "tr_10", "net_V1 [idle -> link_state_feedback : COLLECT || TIME_OUT / ]")
				FSM_CASE_TRANSIT (4, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_1", "net_V1 [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (rx_rcv) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "rx_rcv", state2_enter_exec, "net_V1 [rx_rcv enter execs]")
				FSM_PROFILE_SECTION_IN ("net_V1 [rx_rcv enter execs]", state2_enter_exec)
				{
				int dest;
				int pk_interact_num;
				int nei_num;
				int nei_id[8];
				
				
				//收到不同类型包的行为
				pkptr=op_pk_get(op_intrpt_strm());
				op_pk_nfd_get (pkptr, "TYPE", &type);
				
				if(type==6)//向交互节点发送的上报帧
					{
					op_pk_nfd_get (pkptr, "Num", &pk_interact_num);
					op_pk_nfd_get (pkptr, "DEST", &dest);
					if(dest==my_address && interact_pk_num != pk_interact_num) op_pk_destroy(pkptr);
					else if(dest!=my_address && interact_pk_num-1 != pk_interact_num) op_pk_destroy(pkptr);
					else
						{
						if(dest!=my_address)
							{
							op_pk_nfd_set (pkptr, "Next_Hop", to_interact_next_hop);
							op_pk_send(pkptr,TX_OUT);
							printf("get zhongzhuan pkkkkkkkkkkkk,\n");
							}
						else/////我是交互节点
							{
							link_interact_pk_num++;
							op_pk_nfd_get (pkptr, "Source",&source);
							op_pk_nfd_get (pkptr, "Nei_num",&nei_num);
							op_pk_nfd_get (pkptr, "Nei_address_0", &nei_id[0]);
							op_pk_nfd_get (pkptr, "Nei_address_1", &nei_id[1]);
							op_pk_nfd_get (pkptr, "Nei_address_2", &nei_id[2]);
							op_pk_nfd_get (pkptr, "Nei_address_3", &nei_id[3]);
							op_pk_nfd_get (pkptr, "Nei_address_4", &nei_id[4]);
							op_pk_nfd_get (pkptr, "Nei_address_5", &nei_id[5]);
							op_pk_nfd_get (pkptr, "Nei_address_6", &nei_id[6]);
							op_pk_nfd_get (pkptr, "Nei_address_7", &nei_id[7]);
							printf("交互节点收到pk:%d\n",source);
							for(i=0;i<nei_num;i++)
								topo[source][nei_id[i]]=1;///更新topo矩阵
							
							if(link_interact_pk_num==12)//collect finish!!!!!!!!!!!!!!!!(need to chang!)
								{
								printf("收集完毕！！！\n");
								op_ev_cancel(evh);
								op_intrpt_schedule_self(op_sim_time(),COLLECT_FINISH);
								}
							//获得节点位置并记录
							}
						}	
					}
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (rx_rcv) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "rx_rcv", "net_V1 [rx_rcv exit execs]")


			/** state (rx_rcv) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "rx_rcv", "idle", "tr_5", "net_V1 [rx_rcv -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (src_rcv) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "src_rcv", state3_enter_exec, "net_V1 [src_rcv enter execs]")
				FSM_PROFILE_SECTION_IN ("net_V1 [src_rcv enter execs]", state3_enter_exec)
				{
				/*
				pkptr =  op_pk_get (SRC_IN);
				op_pk_nfd_get (pkptr, "TYPE", &type);
				
				if(type==0)//QWZ
					{
					op_pk_nfd_set (pkptr, "Nei_num", nei_count);
					op_pk_nfd_set (pkptr, "Slot", my_slot);
					t_c=0;
					for(i=0;i<24;i++) nei[i]=0xFF;
					for(i=0;i<24;i++)
						{
						if(my_neighbor[i][0]==1)
							{
							nei[t_c]=i;
							t_c++;
							}
						}
					op_pk_nfd_set (pkptr, "Nei_address_0", nei[0]);
					op_pk_nfd_set (pkptr, "Nei_address_1", nei[1]);
					op_pk_nfd_set (pkptr, "Nei_address_2", nei[2]);
					op_pk_nfd_set (pkptr, "Nei_address_3", nei[3]);
					op_pk_nfd_set (pkptr, "Nei_address_4", nei[4]);
					op_pk_nfd_set (pkptr, "Nei_address_5", nei[5]);
					op_pk_nfd_set (pkptr, "Nei_address_6", nei[6]);
					op_pk_nfd_set (pkptr, "Nei_address_7", nei[7]);//装包
					
					op_pk_send(pkptr,TX_OUT);//send to mac
					
					printf("%d	QWZ pk send to mac\n",my_id);
					
					for(i=0;i<24;i++)
						for(j=0;j<2;j++) my_neighbor[i][j]=0xFF;
					nei_count=0;
					my_two_nei_count_sum=0;
					for(i=0;i<24;i++) my_two_nei[i]=0xFF;//一帧清空一次
					}
				*/
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (src_rcv) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "src_rcv", "net_V1 [src_rcv exit execs]")


			/** state (src_rcv) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "src_rcv", "idle", "tr_7", "net_V1 [src_rcv -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (interact) enter executives **/
			FSM_STATE_ENTER_FORCED (4, "interact", state4_enter_exec, "net_V1 [interact enter execs]")
				FSM_PROFILE_SECTION_IN ("net_V1 [interact enter execs]", state4_enter_exec)
				{
				printf("交互到达%d\n",my_address);
				printf("time:%f\n",op_sim_time());
				if(interactive_id != my_address)
					{
					pkptr=op_pk_create_fmt("link_report");
					op_pk_nfd_set(pkptr,"SEND",my_address);
					op_pk_nfd_set(pkptr,"TYPE",6);
					op_pk_nfd_set(pkptr,"Source",my_address);
					op_pk_nfd_set(pkptr,"DEST",interactive_id);
					op_pk_nfd_set(pkptr,"Next_Hop",to_interact_next_hop);
					op_pk_nfd_set(pkptr,"Num",interact_pk_num);
					
					op_pk_send(pkptr,TX_OUT);
					printf("不是交互节点，生成pk发往tdma\n");
					
					interact_pk_num+=1;
					if(interact_pk_num==16) interact_pk_num=0;//Num
					}
				
				if(interactive_id == my_address)
					{
					evh=op_intrpt_schedule_self(op_sim_time()+180,TIME_OUT_SIGNAL);
					printf("是交互节点，开启定时器\n");
					}
				op_intrpt_schedule_self(op_sim_time()+200,INTACT_PK_SEND);
				}
				FSM_PROFILE_SECTION_OUT (state4_enter_exec)

			/** state (interact) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "interact", "net_V1 [interact exit execs]")


			/** state (interact) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "interact", "idle", "tr_9", "net_V1 [interact -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (link_state_feedback) enter executives **/
			FSM_STATE_ENTER_FORCED (5, "link_state_feedback", state5_enter_exec, "net_V1 [link_state_feedback enter execs]")
				FSM_PROFILE_SECTION_IN ("net_V1 [link_state_feedback enter execs]", state5_enter_exec)
				{
				//packup
				printf("ready to pk up to ground\n");
				printf("time:%f\n",op_sim_time());
				for(i=0;i<13;i++)///////////////////////test for 13
					{
					for(j=0;j<13;j++)
						printf("%d   ",topo[i][j]);
					printf("\n");
					}
				
				
				//ready for next circle
				interact_pk_num+=1;
				if(interact_pk_num==16) interact_pk_num=0;//Num
				
				link_interact_pk_num=0;//pk collection
				
				for(i=0;i<24;i++)
					for(j=0;j<24;j++) topo[i][j]=0;//topo
				}
				FSM_PROFILE_SECTION_OUT (state5_enter_exec)

			/** state (link_state_feedback) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "link_state_feedback", "net_V1 [link_state_feedback exit execs]")


			/** state (link_state_feedback) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "link_state_feedback", "idle", "tr_11", "net_V1 [link_state_feedback -> idle : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"net_V1")
		}
	}




void
_op_net_V1_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_net_V1_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_net_V1_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_net_V1_svar function. */
#undef my_address
#undef my_id
#undef my_node_id
#undef type
#undef interactive_id
#undef to_interact_next_hop
#undef interact_pk_num
#undef topo
#undef link_interact_pk_num
#undef evh

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_net_V1_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_net_V1_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (net_V1)",
		sizeof (net_V1_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_net_V1_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	net_V1_state * ptr;
	FIN_MT (_op_net_V1_alloc (obtype))

	ptr = (net_V1_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "net_V1 [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_net_V1_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	net_V1_state		*prs_ptr;

	FIN_MT (_op_net_V1_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (net_V1_state *)gen_ptr;

	if (strcmp ("my_address" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->my_address);
		FOUT
		}
	if (strcmp ("my_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->my_id);
		FOUT
		}
	if (strcmp ("my_node_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->my_node_id);
		FOUT
		}
	if (strcmp ("type" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->type);
		FOUT
		}
	if (strcmp ("interactive_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->interactive_id);
		FOUT
		}
	if (strcmp ("to_interact_next_hop" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->to_interact_next_hop);
		FOUT
		}
	if (strcmp ("interact_pk_num" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->interact_pk_num);
		FOUT
		}
	if (strcmp ("topo" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->topo);
		FOUT
		}
	if (strcmp ("link_interact_pk_num" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->link_interact_pk_num);
		FOUT
		}
	if (strcmp ("evh" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->evh);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

