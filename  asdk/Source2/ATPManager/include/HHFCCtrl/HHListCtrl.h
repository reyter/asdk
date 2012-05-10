#pragma once
#include "HHScrollBar.h"

//��ֵ����
#define ID_KEYDOWN_FIRST		32000
#define ID_KEYDOWN_HLOCAL		32001
#define ID_KEYDOWN_VLOCAL		32002
#define ID_KEYDOWN_SETCUR		32003
#define ID_KEYDOWN_NEXTPAGE		32004	//��һҳ
#define ID_KEYDOWN_PREPAGE		32005	//��һҳ
#define ID_KEYDOWN_LEFTTYPE		32006
#define ID_KEYDOWN_FONTSIZE		32007
#define ID_KEYDOWN_HELP			32008
#define ID_SAVEMODIFY			32010

#define ID_MOUSEWHEEL_UP		32020
#define ID_MOUSEWHEEL_DOWN		32021
#define ID_MOUSEWHEEL_LEFT		32022
#define ID_MOUSEWHEEL_RIGHT		32023
//�����
#define ID_KEYDOWN_UP						32100
#define ID_KEYDOWN_UP_CTRL					32101
#define ID_KEYDOWN_UP_ALT					32102
#define ID_KEYDOWN_UP_SHIFT					32103
#define ID_KEYDOWN_UP_CTRL_ALT				32104
#define ID_KEYDOWN_UP_SHIFT_CTRL			32105
#define ID_KEYDOWN_UP_SHIFT_ALT				32106
#define ID_KEYDOWN_UP_SHIFT_CTRL_ALT		32107
#define ID_KEYDOWN_DOWN						32108
#define ID_KEYDOWN_DOWN_CTRL				32109
#define ID_KEYDOWN_DOWN_ALT					32110
#define ID_KEYDOWN_DOWN_SHIFT				32111
#define ID_KEYDOWN_DOWN_CTRL_ALT			32112
#define ID_KEYDOWN_DOWN_SHIFT_CTRL			32113
#define ID_KEYDOWN_DOWN_SHIFT_ALT			32114
#define ID_KEYDOWN_DOWN_SHIFT_CTRL_ALT		32115
#define ID_KEYDOWN_LEFT						32116
#define ID_KEYDOWN_LEFT_CTRL				32117
#define ID_KEYDOWN_LEFT_ALT					32118
#define ID_KEYDOWN_LEFT_SHIFT				32119
#define ID_KEYDOWN_LEFT_CTRL_ALT			32120
#define ID_KEYDOWN_LEFT_SHIFT_CTRL			32121
#define ID_KEYDOWN_LEFT_SHIFT_ALT			32122
#define ID_KEYDOWN_LEFT_SHIFT_CTRL_ALT		32123
#define ID_KEYDOWN_RIGHT					32124
#define ID_KEYDOWN_RIGHT_CTRL				32125
#define ID_KEYDOWN_RIGHT_ALT				32126
#define ID_KEYDOWN_RIGHT_SHIFT				32127
#define ID_KEYDOWN_RIGHT_CTRL_ALT			32128
#define ID_KEYDOWN_RIGHT_SHIFT_CTRL			32129
#define ID_KEYDOWN_RIGHT_SHIFT_ALT			32130
#define ID_KEYDOWN_RIGHT_SHIFT_CTRL_ALT		32131
#define ID_KEYDOWN_PGUP						32132
#define ID_KEYDOWN_PGUP_CTRL				32133
#define ID_KEYDOWN_PGUP_ALT					32134
#define ID_KEYDOWN_PGUP_SHIFT				32135
#define ID_KEYDOWN_PGUP_CTRL_ALT			32136
#define ID_KEYDOWN_PGUP_SHIFT_CTRL			32137
#define ID_KEYDOWN_PGUP_SHIFT_ALT			32138
#define ID_KEYDOWN_PGUP_SHIFT_CTRL_ALT		32139
#define ID_KEYDOWN_PGDN						32140
#define ID_KEYDOWN_PGDN_CTRL				32141
#define ID_KEYDOWN_PGDN_ALT					32142
#define ID_KEYDOWN_PGDN_SHIFT				32143
#define ID_KEYDOWN_PGDN_CTRL_ALT			32144
#define ID_KEYDOWN_PGDN_SHIFT_CTRL			32145
#define ID_KEYDOWN_PGDN_SHIFT_ALT			32146
#define ID_KEYDOWN_PGDN_SHIFT_CTRL_ALT		32147
#define ID_KEYDOWN_HOME						32148
#define ID_KEYDOWN_HOME_CTRL				32149
#define ID_KEYDOWN_HOME_ALT					32150
#define ID_KEYDOWN_HOME_SHIFT				32151
#define ID_KEYDOWN_HOME_CTRL_ALT			32152
#define ID_KEYDOWN_HOME_SHIFT_CTRL			32153
#define ID_KEYDOWN_HOME_SHIFT_ALT			32154
#define ID_KEYDOWN_HOME_SHIFT_CTRL_ALT		32155
#define ID_KEYDOWN_END						32156
#define ID_KEYDOWN_END_CTRL					32157
#define ID_KEYDOWN_END_ALT					32158
#define ID_KEYDOWN_END_SHIFT				32159
#define ID_KEYDOWN_END_CTRL_ALT				32160
#define ID_KEYDOWN_END_SHIFT_CTRL			32161
#define ID_KEYDOWN_END_SHIFT_ALT			32162
#define ID_KEYDOWN_END_SHIFT_CTRL_ALT		32163
#define ID_KEYDOWN_INSERT					32164
#define ID_KEYDOWN_INSERT_CTRL				32165
#define ID_KEYDOWN_INSERT_ALT				32166
#define ID_KEYDOWN_INSERT_SHIFT				32167
#define ID_KEYDOWN_INSERT_CTRL_ALT			32168
#define ID_KEYDOWN_INSERT_SHIFT_CTRL		32169
#define ID_KEYDOWN_INSERT_SHIFT_ALT			32170
#define ID_KEYDOWN_INSERT_SHIFT_CTRL_ALT	32171
#define ID_KEYDOWN_DELETE					32172
#define ID_KEYDOWN_DELETE_CTRL				32173
#define ID_KEYDOWN_DELETE_ALT				32174
#define ID_KEYDOWN_DELETE_SHIFT				32175
#define ID_KEYDOWN_DELETE_CTRL_ALT			32176
#define ID_KEYDOWN_DELETE_SHIFT_CTRL		32177
#define ID_KEYDOWN_DELETE_SHIFT_ALT			32178
#define ID_KEYDOWN_DELETE_SHIFT_CTRL_ALT	32179
#define ID_KEYDOWN_RETURN					32180
#define ID_KEYDOWN_RETURN_CTRL				32181
#define ID_KEYDOWN_RETURN_ALT				32182
#define ID_KEYDOWN_RETURN_SHIFT				32183
#define ID_KEYDOWN_RETURN_CTRL_ALT			32184
#define ID_KEYDOWN_RETURN_SHIFT_CTRL		32185
#define ID_KEYDOWN_RETURN_SHIFT_ALT			32186
#define ID_KEYDOWN_RETURN_SHIFT_CTRL_ALT	32187
#define ID_KEYDOWN_SPACE					32188
#define ID_KEYDOWN_SPACE_CTRL				32189
#define ID_KEYDOWN_SPACE_ALT				32190
#define ID_KEYDOWN_SPACE_SHIFT				32191
#define ID_KEYDOWN_SPACE_CTRL_ALT			32192
#define ID_KEYDOWN_SPACE_SHIFT_CTRL			32193
#define ID_KEYDOWN_SPACE_SHIFT_ALT			32194
#define ID_KEYDOWN_SPACE_SHIFT_CTRL_ALT		32195
#define ID_KEYDOWN_BKSP						32196
#define ID_KEYDOWN_BKSP_CTRL				32197
#define ID_KEYDOWN_BKSP_ALT					32198
#define ID_KEYDOWN_BKSP_SHIFT				32199
#define ID_KEYDOWN_BKSP_CTRL_ALT			32200
#define ID_KEYDOWN_BKSP_SHIFT_CTRL			32201
#define ID_KEYDOWN_BKSP_SHIFT_ALT			32202
#define ID_KEYDOWN_BKSP_SHIFT_CLTR_ALT		32203
#define ID_KEYDOWN_TAB						32204
#define ID_KEYDOWN_TAB_CTRL					32205
#define ID_KEYDOWN_TAB_ALT					32206
#define ID_KEYDOWN_TAB_SHIFT				32207
#define ID_KEYDOWN_TAB_CTRL_ALT				32208
#define ID_KEYDOWN_TAB_SHIFT_CLTR			32209
#define ID_KEYDOWN_TAB_SHIFT_ALT			32210
#define ID_KEYDOWN_TAB_SHIFT_CTRL_ALT		32211
#define ID_KEYDOWN_ESCAPE					32212
#define ID_KEYDOWN_ESCAPE_CTRL				32213
#define ID_KEYDOWN_ESCAPE_ALT				32214
#define ID_KEYDOWN_ESCAPE_SHIFT				32215
#define ID_KEYDOWN_ESCAPE_CTRL_ALT			32216
#define ID_KEYDOWN_ESCAPE_SHIFT_CTRL		32217
#define ID_KEYDOWN_ESCAPE_SHIFT_ALT			32218
#define ID_KEYDOWN_ESCAPE_SHIFT_CTRL_ALT	32219

//�����
#define ID_KEYDOWN_ADD   		32260
#define ID_KEYDOWN_ADD_CTRL		32261
#define ID_KEYDOWN_ADD_ALT  	32262
#define ID_KEYDOWN_ADD_SHIFT    32263
#define ID_KEYDOWN_SUB   		32264
#define ID_KEYDOWN_SUB_CTRL		32269
#define ID_KEYDOWN_SUB_ALT  	32266
#define ID_KEYDOWN_SUB_SHIFT    32267
#define ID_KEYDOWN_MUL   		32268
#define ID_KEYDOWN_MUL_CTRL		32269
#define ID_KEYDOWN_MUL_ALT  	32270
#define ID_KEYDOWN_MUL_SHIFT    32271
#define ID_KEYDOWN_DIV   		32272
#define ID_KEYDOWN_DIV_CTRL		32273
#define ID_KEYDOWN_DIV_ALT  	32274
#define ID_KEYDOWN_DIV_SHIFT    32275

#define ID_KEYDOWN_DOT     		32276
#define ID_KEYDOWN_DOT_CTRL		32277
#define ID_KEYDOWN_DOT_ALT  	32278
#define ID_KEYDOWN_DOT_SHIFT    32279

//���ܼ�
#define ID_KEYDOWN_F1			32300
#define ID_KEYDOWN_F1_CTRL		32301
#define ID_KEYDOWN_F1_ALT		32302
#define ID_KEYDOWN_F1_SHIFT		32303
#define ID_KEYDOWN_F2			32304
#define ID_KEYDOWN_F2_CTRL		32305
#define ID_KEYDOWN_F2_ALT		32306
#define ID_KEYDOWN_F2_SHIFT		32307
#define ID_KEYDOWN_F3			32308
#define ID_KEYDOWN_F3_CTRL		32309
#define ID_KEYDOWN_F3_ALT		32310
#define ID_KEYDOWN_F3_SHIFT		32311
#define ID_KEYDOWN_F4			32312
#define ID_KEYDOWN_F4_CTRL		32313
#define ID_KEYDOWN_F4_ALT		32314
#define ID_KEYDOWN_F4_SHIFT		32315
#define ID_KEYDOWN_F5			32316
#define ID_KEYDOWN_F5_CTRL		32317
#define ID_KEYDOWN_F5_ALT		32318
#define ID_KEYDOWN_F5_SHIFT		32319
#define ID_KEYDOWN_F6			32320
#define ID_KEYDOWN_F6_CTRL		32321
#define ID_KEYDOWN_F6_ALT		32322
#define ID_KEYDOWN_F6_SHIFT		32323
#define ID_KEYDOWN_F7			32324
#define ID_KEYDOWN_F7_CTRL		32325
#define ID_KEYDOWN_F7_ALT		32326
#define ID_KEYDOWN_F7_SHIFT		32327
#define ID_KEYDOWN_F8			32328
#define ID_KEYDOWN_F8_CTRL		32329
#define ID_KEYDOWN_F8_ALT		32330
#define ID_KEYDOWN_F8_SHIFT		32331
#define ID_KEYDOWN_F9			32332
#define ID_KEYDOWN_F9_CTRL		32333
#define ID_KEYDOWN_F9_ALT		32334
#define ID_KEYDOWN_F9_SHIFT		32335
#define ID_KEYDOWN_F10			32336
#define ID_KEYDOWN_F10_CTRL		32337
#define ID_KEYDOWN_F10_ALT		32338
#define ID_KEYDOWN_F10_SHIFT	32339
#define ID_KEYDOWN_F11			32340
#define ID_KEYDOWN_F11_CTRL		32341
#define ID_KEYDOWN_F11_ALT		32342
#define ID_KEYDOWN_F11_SHIFT	32343
#define ID_KEYDOWN_F12			32344
#define ID_KEYDOWN_F12_CTRL		32345
#define ID_KEYDOWN_F12_ALT		32346
#define ID_KEYDOWN_F12_SHIFT	32347
#define ID_KEYDOWN_F13			32348
#define ID_KEYDOWN_F13_CTRL		32349
#define ID_KEYDOWN_F13_ALT		32350
#define ID_KEYDOWN_F13_SHIFT	32351
#define ID_KEYDOWN_F14			32352
#define ID_KEYDOWN_F14_CTRL		32353
#define ID_KEYDOWN_F14_ALT		32354
#define ID_KEYDOWN_F14_SHIFT	32355
#define ID_KEYDOWN_F15			32356
#define ID_KEYDOWN_F15_CTRL		32357
#define ID_KEYDOWN_F15_ALT		32358
#define ID_KEYDOWN_F15_SHIFT	32359
#define ID_KEYDOWN_F16			32360
#define ID_KEYDOWN_F16_CTRL		32361
#define ID_KEYDOWN_F16_ALT		32362
#define ID_KEYDOWN_F16_SHIFT	32363
#define ID_KEYDOWN_F17			32364
#define ID_KEYDOWN_F17_CTRL		32365
#define ID_KEYDOWN_F17_ALT		32366
#define ID_KEYDOWN_F17_SHIFT	32367
#define ID_KEYDOWN_F18			32368
#define ID_KEYDOWN_F18_CTRL		32369
#define ID_KEYDOWN_F18_ALT		32370
#define ID_KEYDOWN_F18_SHIFT	32371
#define ID_KEYDOWN_F19			32372
#define ID_KEYDOWN_F19_CTRL		32373
#define ID_KEYDOWN_F19_ALT		32374
#define ID_KEYDOWN_F19_SHIFT	32375
#define ID_KEYDOWN_F20			32376
#define ID_KEYDOWN_F20_CTRL		32377
#define ID_KEYDOWN_F20_ALT		32378
#define ID_KEYDOWN_F20_SHIFT	32379
#define ID_KEYDOWN_F21			32380
#define ID_KEYDOWN_F21_CTRL		32381
#define ID_KEYDOWN_F21_ALT		32382
#define ID_KEYDOWN_F21_SHIFT	32383
#define ID_KEYDOWN_F22			32384
#define ID_KEYDOWN_F22_CTRL		32385
#define ID_KEYDOWN_F22_ALT		32386
#define ID_KEYDOWN_F22_SHIFT	32387
#define ID_KEYDOWN_F23			32388
#define ID_KEYDOWN_F23_CTRL		32389
#define ID_KEYDOWN_F23_ALT		32390
#define ID_KEYDOWN_F23_SHIFT	32391
#define ID_KEYDOWN_F24			32392
#define ID_KEYDOWN_F24_CTRL		32393
#define ID_KEYDOWN_F24_ALT		32394
#define ID_KEYDOWN_F24_SHIFT	32395

//���ּ�
#define ID_KEYDOWN_0        	32400
#define ID_KEYDOWN_0_CTRL       32401
#define ID_KEYDOWN_0_ALT        32402
#define ID_KEYDOWN_0_SHIFT      32403
#define ID_KEYDOWN_1        	32404
#define ID_KEYDOWN_1_CTRL       32405
#define ID_KEYDOWN_1_ALT        32406
#define ID_KEYDOWN_1_SHIFT      32407
#define ID_KEYDOWN_2        	32408
#define ID_KEYDOWN_2_CTRL       32409
#define ID_KEYDOWN_2_ALT        32410
#define ID_KEYDOWN_2_SHIFT      32411
#define ID_KEYDOWN_3        	32412
#define ID_KEYDOWN_3_CTRL       32413
#define ID_KEYDOWN_3_ALT        32414
#define ID_KEYDOWN_3_SHIFT      32415
#define ID_KEYDOWN_4        	32416
#define ID_KEYDOWN_4_CTRL       32417
#define ID_KEYDOWN_4_ALT        32418
#define ID_KEYDOWN_4_SHIFT      32419
#define ID_KEYDOWN_5        	32420
#define ID_KEYDOWN_5_CTRL       32421
#define ID_KEYDOWN_5_ALT        32422
#define ID_KEYDOWN_5_SHIFT      32423
#define ID_KEYDOWN_6        	32424
#define ID_KEYDOWN_6_CTRL       32425
#define ID_KEYDOWN_6_ALT        32426
#define ID_KEYDOWN_6_SHIFT      32427
#define ID_KEYDOWN_7        	32428
#define ID_KEYDOWN_7_CTRL       32429
#define ID_KEYDOWN_7_ALT        32430
#define ID_KEYDOWN_7_SHIFT      32431
#define ID_KEYDOWN_8        	32432
#define ID_KEYDOWN_8_CTRL       32433
#define ID_KEYDOWN_8_ALT        32434
#define ID_KEYDOWN_8_SHIFT      32435
#define ID_KEYDOWN_9        	32436
#define ID_KEYDOWN_9_CTRL       32437
#define ID_KEYDOWN_9_ALT        32438
#define ID_KEYDOWN_9_SHIFT      32449
//��ĸ
#define ID_KEYDOWN_A		    32450
#define ID_KEYDOWN_A_CTRL		32451
#define ID_KEYDOWN_A_ALT		32452
#define ID_KEYDOWN_A_SHIFT		32453
#define ID_KEYDOWN_B		    32454
#define ID_KEYDOWN_B_CTRL		32455
#define ID_KEYDOWN_B_ALT		32456
#define ID_KEYDOWN_B_SHIFT		32457
#define ID_KEYDOWN_C		    32458
#define ID_KEYDOWN_C_CTRL		32459
#define ID_KEYDOWN_C_ALT		32460
#define ID_KEYDOWN_C_SHIFT		32461
#define ID_KEYDOWN_D		    32462
#define ID_KEYDOWN_D_CTRL		32463
#define ID_KEYDOWN_D_ALT		32464
#define ID_KEYDOWN_D_SHIFT		32465
#define ID_KEYDOWN_E		    32466
#define ID_KEYDOWN_E_CTRL		32467
#define ID_KEYDOWN_E_ALT		32468
#define ID_KEYDOWN_E_SHIFT		32469
#define ID_KEYDOWN_F		    32470
#define ID_KEYDOWN_F_CTRL		32471
#define ID_KEYDOWN_F_ALT		32472
#define ID_KEYDOWN_F_SHIFT		32473
#define ID_KEYDOWN_G		    32474
#define ID_KEYDOWN_G_CTRL		32475
#define ID_KEYDOWN_G_ALT		32476
#define ID_KEYDOWN_G_SHIFT		32477
#define ID_KEYDOWN_H		    32478
#define ID_KEYDOWN_H_CTRL		32479
#define ID_KEYDOWN_H_ALT		32480
#define ID_KEYDOWN_H_SHIFT		32481
#define ID_KEYDOWN_I		    32482
#define ID_KEYDOWN_I_CTRL		32483
#define ID_KEYDOWN_I_ALT		32484
#define ID_KEYDOWN_I_SHIFT		32485
#define ID_KEYDOWN_J		    32486
#define ID_KEYDOWN_J_CTRL		32487
#define ID_KEYDOWN_J_ALT		32488
#define ID_KEYDOWN_J_SHIFT		32489
#define ID_KEYDOWN_K		    32490
#define ID_KEYDOWN_K_CTRL		32491
#define ID_KEYDOWN_K_ALT		32492
#define ID_KEYDOWN_K_SHIFT		32493
#define ID_KEYDOWN_L		    32494
#define ID_KEYDOWN_L_CTRL		32495
#define ID_KEYDOWN_L_ALT		32496
#define ID_KEYDOWN_L_SHIFT		32497
#define ID_KEYDOWN_M		    32498
#define ID_KEYDOWN_M_CTRL		32499
#define ID_KEYDOWN_M_ALT		32500
#define ID_KEYDOWN_M_SHIFT		32501
#define ID_KEYDOWN_N		    32502
#define ID_KEYDOWN_N_CTRL		32503
#define ID_KEYDOWN_N_ALT		32504
#define ID_KEYDOWN_N_SHIFT		32505
#define ID_KEYDOWN_O		    32506
#define ID_KEYDOWN_O_CTRL		32507
#define ID_KEYDOWN_O_ALT		32508
#define ID_KEYDOWN_O_SHIFT		32509
#define ID_KEYDOWN_P		    32510
#define ID_KEYDOWN_P_CTRL		32511
#define ID_KEYDOWN_P_ALT		32512
#define ID_KEYDOWN_P_SHIFT		32513
#define ID_KEYDOWN_Q		    32514
#define ID_KEYDOWN_Q_CTRL		32515
#define ID_KEYDOWN_Q_ALT		32516
#define ID_KEYDOWN_Q_SHIFT		32517
#define ID_KEYDOWN_R		    32518
#define ID_KEYDOWN_R_CTRL		32519
#define ID_KEYDOWN_R_ALT		32520
#define ID_KEYDOWN_R_SHIFT		32521
#define ID_KEYDOWN_S		    32522
#define ID_KEYDOWN_S_CTRL		32523
#define ID_KEYDOWN_S_ALT		32524
#define ID_KEYDOWN_S_SHIFT		32525
#define ID_KEYDOWN_T		    32526
#define ID_KEYDOWN_T_CTRL		32527
#define ID_KEYDOWN_T_ALT		32528
#define ID_KEYDOWN_T_SHIFT		32529
#define ID_KEYDOWN_U		    32530
#define ID_KEYDOWN_U_CTRL		32531
#define ID_KEYDOWN_U_ALT		32532
#define ID_KEYDOWN_U_SHIFT		32533
#define ID_KEYDOWN_V		    32534
#define ID_KEYDOWN_V_CTRL		32535
#define ID_KEYDOWN_V_ALT		32536
#define ID_KEYDOWN_V_SHIFT		32537
#define ID_KEYDOWN_W		    32538
#define ID_KEYDOWN_W_CTRL		32539
#define ID_KEYDOWN_W_ALT		32540
#define ID_KEYDOWN_W_SHIFT		32541
#define ID_KEYDOWN_X		    32542
#define ID_KEYDOWN_X_CTRL		32543
#define ID_KEYDOWN_X_ALT		32544
#define ID_KEYDOWN_X_SHIFT		32545
#define ID_KEYDOWN_Y		    32546
#define ID_KEYDOWN_Y_CTRL		32547
#define ID_KEYDOWN_Y_ALT		32548
#define ID_KEYDOWN_Y_SHIFT		32549
#define ID_KEYDOWN_Z		    32550
#define ID_KEYDOWN_Z_CTRL		32551
#define ID_KEYDOWN_Z_ALT		32552
#define ID_KEYDOWN_Z_SHIFT		32553
//����
#define ID_KEYDOWN_ZKH    		32560		//������
#define ID_KEYDOWN_ZKH_CTRL		32561		//������
#define ID_KEYDOWN_ZKH_ALT  	32562		//������
#define ID_KEYDOWN_ZKH_SHIFT    32563		//������
#define ID_KEYDOWN_YKH    		32564		//������
#define ID_KEYDOWN_YKH_CTRL		32565		//������
#define ID_KEYDOWN_YKH_ALT  	32566		//������
#define ID_KEYDOWN_YKH_SHIFT    32567		//������
#define ID_KEYDOWN_DH    		32568		//�ٺ�
#define ID_KEYDOWN_DH_CTRL		32569		//�ٺ�
#define ID_KEYDOWN_DH_ALT  		32570		//�ٺ�
#define ID_KEYDOWN_DH_SHIFT		32571		//�ٺ�

#define ID_KEYDOWN_DYH    		32572		//������
#define ID_KEYDOWN_DYH_CTRL		32573		//������
#define ID_KEYDOWN_DYH_ALT  	32574		//������
#define ID_KEYDOWN_SYH    		32571		//˫����
#define ID_KEYDOWN_FH    		32575		//�ֺ�
#define ID_KEYDOWN_FH_CTRL		32577		//�ֺ�
#define ID_KEYDOWN_FH_ALT  		32578		//�ֺ�
#define ID_KEYDOWN_MH    		32579		//ð��

#define HHIDLT_HEAD			0x00000001	//�б�ͷ
#define HHIDLT_TITLE		0x00000002	//�б���
#define HHIDLT_INPUT		0x00000004	//��������
#define HHIDLT_NODRAG		0x00000010	//����������
#define HHIDLT_NOSORT		0x00000020	//������
#define HHIDLT_NOADJHEADORD	0x00000040	//���ܵ�����ͷ˳��
#define HHIDLT_NOADJHEADWID	0x00000080	//���ܵ�����ͷ���
#define HHIDLT_NOHEADTIP	0x00000100	//�ޱ�ͷTip
#define HHIDLT_NOITEMTIP	0x00000200	//������Tip
#define HHIDLT_HORIZONLIST	0x00001000	//ˮƽ����
#define HHIDLT_NOCURSOR		0x00002000	//�Ǽ���ʱ����ʾ���
#define HHIDLT_ONLYCURBOX	0x00004000	//�߿���ʱ͸����걳��
#define HHIDLT_CHANGEGEDBOX	0x00008000	//���ݱ仯ʱ�ñ߿�ͻ����ʾ�仯����//���ʱ͸����걳��
#define HHIDLT_GROUPHEAD	0x00010000	//�����ͷ

#define HHIDTL_CHECKBOX		0x00000001	//��Check��
#define HHIDTL_HASLINES		0x00000002	//������
#define HHIDTL_HASBUTTONS	0x00000004	//��չ����ť
#define HHIDTL_ROOTLINE		0x00000008	//�и�����
#define HHIDTL_ICON			0x00000010	//��ͼ��

#define HHIDLTPROP_TITLE	0x00000001	//����
#define HHIDLTPROP_HEAD		0x00000002	//��ͷ
#define HHIDLTPROP_SELCUR	0x00000004	//ѡ����
#define HHIDLTPROP_MULTISEL	0x00000008	//��ѡ
#define HHIDLTPROP_ALL		0x0000000f


#define HHIDLT_DEF_OWNERDRAW	0x0ffffff0	//�Ի�Item
#define HHIDLT_DEF_IMAGELIST	0x0ffffff1	//CImageList

#define HHIDLT_DEF_TA_LEFT		0x00010000	//�����
#define HHIDLT_DEF_TA_CENTER	0x00020000	//�ж���
#define HHIDLT_DEF_TA_RIGHT		0x00030000	//�Ҷ���
#define HHIDLT_DEF_TT_CHN		0x00040000	//����

#define HHIDLT_DEF_CHECKBOX		'j'			//ѡ���
#define HHIDLT_DEF_ORDER		'o'			//���
#define HHIDLT_DEF_DATE			't'			//����(YMD)
#define HHIDLT_DEF_TIME			'h'			//ʱ��(HMS)
#define HHIDLT_DEF_MDHM			'T'			//����+ʱ��(��+��+ʱ+��)
#define HHIDLT_DEF_YMDHM		0x00001001	//����+ʱ��(��+��+��+ʱ+��)[����]
#define HHIDLT_DEF_ymdhm		0x00001002	//����+ʱ��(��+��+��+ʱ+��)
#define HHIDLT_DEF_ymdhms		0x00001003	//����+ʱ��(��+��+��+ʱ+��+��)
#define HHIDLT_DEF_TIMEHM		0x00001004	//ʱ��(ʱ+��)[����]
#define HHIDLT_DEF_TIMEhm		0x00001005	//ʱ��(ʱ+��)
#define HHIDLT_DEF_CHARS		'c'			//�ַ���
#define HHIDLT_DEF_LONG			'l'			//long
#define HHIDLT_DEF_LONG_SPL		0x00000111	//long  ʹ��','�ָ���ʾ
#define HHIDLT_DEF_ULONG		'u'			//unsigned long
#define HHIDLT_DEF_ULONG_SPL	0x00000121	//unsigned long ʹ��','�ָ���ʾ
#define HHIDLT_DEF_ULONG_KMG	0x00000122	//unsigned long ʹ��'g,m,g'��ʾ
#define HHIDLT_DEF_SIZE_UL		0x00000101	//unsigned long �洢��С
#define HHIDLT_DEF_SIZE_DL		0x00000102	//double		�洢��С
#define HHIDLT_DEF_SHORT		's'			//short
#define HHIDLT_DEF_INT			'n'			//int
#define HHIDLT_DEF_FLOAT		'f'			//float
#define HHIDLT_DEF_FLOAT_SPL	0x00000131	//float ʹ��','�ָ���ʾ
#define HHIDLT_DEF_DOUBLE		'd'			//double
#define HHIDLT_DEF_DOUBLE_SPL	0x00000141	//double ʹ��','�ָ���ʾ
#define HHIDLT_DEF_INT64		'6'			//int64
#define HHIDLT_DEF_INT64_SPL	0x00000151	//int64 ʹ��','�ָ���ʾ
#define HHIDLT_DEF_INT64_KMG	0x00000152	//int64 ʹ��'k,m,g'��ʾ
#define HHIDLT_DEF_PERCENT		'p'			//�ٷֱ�(%)
#define HHIDLT_DEF_CSTRING		0x00008001	//CString
#define HHIDLT_DEF_CFILENAME	0x00008002	//CString(�ļ�����)

#define HHIDLT_DEF_NFP_DN		0x00004001	//�û�DN
#define HHIDLT_DEF_NFP_USERID	0x00004002	//�û�ID
#define HHIDLT_DEF_NFP_USERNAME	0x00004003	//�û�����
#define HHIDLT_DEF_NFP_STATUS	0x00004010	//״̬
#define HHIDLT_DEF_NFP_IP		0x00004011	//IP
#define HHIDLT_DEF_NFP_LOGTIME	0x00004012	//��½ʱ��
#define HHIDLT_DEF_NFP_SEND0	0x00004013	//��ǰ����
#define HHIDLT_DEF_NFP_RECEIVE0	0x00004014	//��ǰ����
#define HHIDLT_DEF_NFP_SEND		0x00004015	//�ܷ���
#define HHIDLT_DEF_NFP_RECEIVE	0x00004016	//�ܽ���
#define HHIDLT_DEF_NFP_CSTRING1	0x00004020	//��Ϣһ
#define HHIDLT_DEF_NFP_CSTRING2	0x00004021	//��Ϣ��
#define HHIDLT_DEF_NFP_COUNT1	0x00004022	//����һ
#define HHIDLT_DEF_NFP_COUNT2	0x00004023	//������

#define ID_LT_RELATION		0x80000000	//Tree
#define ID_LT_RETRACT		0x40000000	//����
#define ID_LT_EXPEND		0x20000000	//չ��
#define ID_LT_LINE			0x10000000
#define ID_LT_LLINE			0x08000000	//Left Line
#define ID_LT_TLINE			0x04000000	//Top Line
#define ID_LT_NEXTL			0x02000000	//Next Line

struct HHFC_FONTSET
{
	int		nSize;
	char	bBold;
	char	bItalic;
	char	strName[29];
	char	bUnderline;
	void    Init(char *name, int size, BOOL bold, BOOL italic)
	{
		bBold=bold;
		bItalic=italic;
		nSize=size;
		memset(strName,0,30);
		strncpy(strName,name,28);
	};
	void	CheckFontSet()
	{
		if(nSize<6||nSize>128||strName[0]==0||!strncmp(strName,"��",2)||strlen(strName)>32) 
		{
			strcpy(strName,"����");
			nSize=12;
			bBold=FALSE;
			bItalic=FALSE;
			bUnderline=FALSE;
		}
	}
};

struct HHFC_LINESET
{
	char     width;
	char     type;
	char     bdraw;
	char	 param;
	COLORREF color;
	void	 Init(char t, char w, COLORREF c, char d=TRUE, char p=0)
	{
		color=c;
		width=w;
		type=t;
		bdraw=d;
		param=0;
	}
};

struct HHLISTCTRL_CHANGESELECTITEM
{
	int nOldItem;
	int nNewItem;
	int nSplit;
	int nOldCol;
	int nNewCol;
};

struct HHLISTSET_FONT
{
	HHFC_FONTSET fontTitle;//��������
	HHFC_FONTSET fontHead; //̧ͷ����
	HHFC_FONTSET fontChn;  //�б�������
	HHFC_FONTSET fontNum;  //�б���������
	HHLISTSET_FONT()
	{
		Init();
	}
	void Init()
	{
		//��������
		fontTitle.Init("����",12,TRUE,FALSE);
		fontHead.Init("����",12,FALSE,FALSE);
		fontChn.Init("����",12,FALSE,FALSE);
		fontNum.Init("����",12,FALSE,FALSE);
	}
};

struct HHLISTSET_COLOR
{
	//����
	COLORREF colorTitle,colorTitleBk,colorTitleBk1;
	//̧ͷ��ɫ
	COLORREF colorHeadFr, colorHeadBk, colorHeadBk1, colorHeadBox;
	//�б�
	COLORREF colorList;
	COLORREF colorListBk, colorListBk1;
	COLORREF colorMultiSel;					
	COLORREF colorMultiSelBk, colorMultiSelBk1;
	//�ָ���
	COLORREF colorVSplitLine, colorHSplitLine, colorLockFieldLine;
	//�����ɫ
	COLORREF colorCur;
	COLORREF colorCurBk, colorCurBk1;
	COLORREF colorNoAct;
	COLORREF colorNoActBk, colorNoActBk1;

	HHLISTSET_COLOR()
	{
		Init();
	}
	void Init()
	{
		colorTitleBk=colorTitleBk1=RGB(255,255,255);
		colorTitle=RGB(255,0,0);

		colorHeadFr=RGB(0,0,0);
		colorHeadBk=::GetSysColor(COLOR_3DFACE);
		colorHeadBk1=::GetSysColor(COLOR_3DFACE)+0x101010;
		colorHeadBox=RGB(160,160,160);

		colorList=RGB(0,0,0);
		colorListBk=RGB(255,255,255);
		colorListBk1=RGB(230,230,230);//RGB(196,255,255);
		colorCur=RGB(254,254,254);
		colorCurBk=RGB(0,0,255);
		colorCurBk1=RGB(0,0,128);
		colorVSplitLine=::GetSysColor(COLOR_3DFACE)-0x101010;
		colorHSplitLine=::GetSysColor(COLOR_3DFACE)-0x101010;
		colorMultiSelBk=colorMultiSelBk1=RGB(181,190,214);
		colorNoActBk=RGB(192,192,192);
		colorNoActBk1=RGB(160,160,160);
		colorMultiSel=RGB(0,0,0);
		colorNoAct=RGB(0,0,0);
		colorLockFieldLine=RGB(0,0,0);
	}
};

struct HHLISTSET_SET
{
	//̧ͷ
	char	bHeadBox;
	char	nHeadBackground;
	char	nCursorBackground;
	//�б�
	char	 nBackground;
	//�ָ���
	char     bVSplitLine, bHSplitLine, bLockFieldLine;
	//�б��м��
	int      nLineSpace;

	HHLISTSET_SET()
	{
		Init();
	}
	void Init()
	{
		nBackground=FALSE;

		bHeadBox=TRUE;
		nHeadBackground=1;
		nCursorBackground=2;

		bHSplitLine=TRUE;
		bVSplitLine=TRUE;

		bLockFieldLine=TRUE;

		nLineSpace=4;
	}
};

//�б�״̬///////////////////////////////////
struct HHLISTSET_STATUS
{
	BOOL	bCursorY,bCursorX,bCursorSplitX;
	int     nColFixeds[2];	//�̶�����
	int		nColLocks[2];	//��������
	int     nCols[2];		//��ҳ����
	int		nLines;			//��ҳ����
	int     nFirstY;
	int		nFirstX[2];
	int		nCursorY;		//�й��λ��
	int     nCursorX[2];	//�й��λ��
	BOOL	bSplit;			//�ָ�˫�б�
	int		nSplit;			//�����б�
	float   fSplit;			//�ָ����
};


//�ļ�����
#define		_A_NSDEX_DRIVER			0x80000000	//������
#define		_A_NSDEX_MYCOMPUTER		0x40000001	//�ҵĵ���
#define		_A_NSDEX_NETNEIGHBOR	0x40000002	//�����ھ�
#define		_A_NSDEX_RECYCLE		0x40000003	//����վ
#define		_A_NSDEX_IE				0x40000004	//IE
#define		_A_NSDEX_CONTROLS		0x40000005	//�������
#define		_A_NSDEX_MYDOCUMENT		0x40001001	//�ҵ��ĵ�
#define		_A_NSDEX_MYPICTURES		0x40001002	//�ҵ�ͼƬ

#define		_A_NSDEX_MYNSDDOCU		0x20000001	//�ҵ�NSD�ĵ���
#define		_A_NSDEX_EZP			0x20000002	//�ױ��

#define		_A_NSDEX_PREDIR			0x10000000	//�ϼ�Ŀ¼

struct HHLISTCTRL_FILELIST
{
	unsigned nAttrib;
	CString strFileName;
	CString strExt;
	double  dSize;
	long	lDate;
	long	lTime;
	int		nStatus;
	HICON	hIcon;
	long	lOffset;
	long    lCRC;
	HHLISTCTRL_FILELIST *pFileList;	//��Ŀ¼�ļ��б�
	int		nFiles;					//��Ŀ¼�ļ�����
	HHLISTCTRL_FILELIST()
	{
		dSize=0;
		lDate=0;
		lTime=0;
		nAttrib=0;
		nStatus=0;
		hIcon=NULL;
		pFileList=NULL;
		nFiles=0;
		//lOffset=0;
		//lCRC=0;
	}
	~HHLISTCTRL_FILELIST()
	{
		if(pFileList) delete[] pFileList;
		DestoryIcon();
	}
	HHLISTCTRL_FILELIST(const HHLISTCTRL_FILELIST& fileinfo)
	{
		operator = (fileinfo);
	}
	HHLISTCTRL_FILELIST& operator =(const HHLISTCTRL_FILELIST& fileinfo)
	{
		strFileName=fileinfo.strFileName;
		strExt=fileinfo.strExt;
		dSize=fileinfo.dSize;
		lDate=fileinfo.lDate;
		lTime=fileinfo.lTime;
		nAttrib=fileinfo.nAttrib;
		nStatus=fileinfo.nStatus;
		hIcon=NULL;
		pFileList=NULL;
		nFiles=0;
		//lOffset=0;
		//lCRC=0;
		return *this;
	}
	BOOL operator ==(const HHLISTCTRL_FILELIST& fileinfo)
	{
		if(strcmp(strFileName,fileinfo.strFileName)) return FALSE;
		if(strcmp(strExt,fileinfo.strExt)) return FALSE;
		if(dSize!=fileinfo.dSize) return FALSE;
		if(lDate!=fileinfo.lDate) return FALSE;
		if(lTime!=fileinfo.lTime) return FALSE;
		if(nAttrib!=fileinfo.nAttrib) return FALSE;
		if(nStatus!=fileinfo.nStatus) return FALSE;
		if(nFiles!=fileinfo.nFiles) return FALSE;
		return TRUE;
	}
	void DestoryIcon()
	{
		if(hIcon)
		{
			::DestroyIcon(hIcon);
			hIcon=NULL;
		}
	}
};

#define HHLISTCTRL_MAXCOLS	128	//�б��������

class AFX_EXT_CLASS CHHListCtrl :	public CWnd
{
	DECLARE_DYNAMIC(CHHListCtrl)
	CRITICAL_SECTION	m_cs;
private:
	BOOL    m_bInitResource;//��Դ��ʼ����־
	BOOL	m_bCaret;
	//ͼ��
	CImageList *m_pDragImage;
	SIZE CaptureDragDropImage(char *strText, CPoint point, int ncolor=ILC_MASK);
	SIZE CaptureDragDropImage(CRect rect, CPoint point,int ncolor=ILC_MASK);
	void ReleaseDragImage();
public:
	CFont	m_fontTitle;	//��������
	CFont	m_fontHead;		//̧ͷ����
	CFont   m_fontChn;		//�б�������
	CFont   m_fontNum;		//�б���������

	CPoint	m_ptLBDown;
	RECT	m_rectClient;
	int		m_nCXHScroll,m_nCYVScroll;

	int     m_nListID[2][HHLISTCTRL_MAXCOLS];	//�б���ID
	int		m_nItemX[2][HHLISTCTRL_MAXCOLS];
	int     m_nLockItems[2];	//������Ŀ��
	CString m_strHead[2][HHLISTCTRL_MAXCOLS];
	RECT    m_rectHeadTip;

	CHHScrollBar m_HScroll[2];		//��ֱ������
	CHHScrollBar m_VScroll[2];		//ˮƽ������
	RECT		 m_rectHScroll[2];
	RECT		 m_rectVScroll[2];
	char    m_nHScrollFlag;
	char    m_nVScrollFlag;
	char	m_bHScrollFlag;
	char	m_bVScrollFlag;

	BOOL	 m_bMarkListHeadItemFlag;
	int      m_nMarkListHeadStyle;
	COLORREF m_ColorMarkListHeadFr;
	COLORREF m_ColorMarkListHeadBk1;
	COLORREF m_ColorMarkListHeadBk2;

	int		m_nAcjustColWidth;
	int		m_nAdjustColOrder;
	int		m_nAdjustColSplit;
	int     m_nPreAdjustCol;
	RECT	m_rectAdjustCol;
	
	int		m_nSplitLine;	//�ָ���λ��

	CPoint  m_ptAdjustPoint;
	CPoint  m_ptDownOffset;
	
	int		m_nListStyle;
	int     m_nTreeStyle;
	CString m_strListTitle;
	char	m_bMultiSelect;	//����ѡ�����
	char	m_bEnableCursor;
	char    m_bResv;

	char    m_bSetFocus;
	char	m_bActive;
	char    m_bFloatHeadFlag;

	char	m_bCustomCtrl[2];	//��������ؼ�(�ڲ�����)
	char    m_CustomFlag[2][HHLISTCTRL_MAXCOLS];
public:
	char    *m_pMultiSelect;//����ѡ���־
	int		m_nMultiSelectSize;
	HHLISTSET_FONT		m_ListFont;
	HHLISTSET_COLOR		m_ListColor;
	HHLISTSET_SET		m_ListSet;
	HHLISTSET_STATUS	m_ListStatus;

	RECT	m_rectListClient;
	RECT	m_rectListTitle;
	RECT	m_rectListHead[2];		//̧ͷ����
	RECT	m_rectListList[2];		//�б�����

	/////////////////////////////////////////////////
	int		m_nTotalLines,m_nTotalCols[2];
	long    m_lTickCount;
	int		m_nLineHeight;
	int		m_nListWidth[2], m_nPageWidth[2];
	int		m_nColPos[2], m_nColLockX[2];

	char	m_bInputDot;	//���������
	char	m_bInputReSet;
	char    m_nVertListCols[2];//ˮƽ�б������

	RECT	m_rectListInput;
	char    m_strInput[64];

public:
	CHHListCtrl(void);
	~CHHListCtrl(void);

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	afx_msg LRESULT OnHHVScroll(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHHHScroll(WPARAM wParam, LPARAM lParam);

protected:
	virtual void OnDraw(CDC *pDC, int nDrawFlag);
	void CalcRect(CDC *pDC);													//���������λ��
	void DrawInput(CDC *pDC);
	void DrawListList(CDC *pDC, int nPaintFlag=0);								//����б�
	void DrawListHead(CDC *pDC, int nPaintFlag=0);								//�������б��̧ͷ
	void DrawOnwerItemCtrl();													//����ؼ�
	int  DrawListLine(CDC *pDC,int record, int nPaintFlag=0, int nCol=-1);		//�������б�ļ�¼
	int  DrawListCol(CDC *pDC, int col, int nPaintFlag=0);
	int  GetFirstXFromCursorX(int nCursorX);
	int  GetLeftRightPage(int nLeft, int nPos);
public:
	void InitResoruce(BOOL bForceInit=FALSE);									//��ʼ���������Դ(�����)
	void SetListSplit(BOOL bSplit=TRUE, int nSplit=0, float fSplit=0.5);

	void SetListStyle(int nListStyle=HHIDLT_HEAD);
	void SetTreeStyle(int nTreeStyle=HHIDTL_CHECKBOX|HHIDTL_HASLINES|HHIDTL_HASBUTTONS|HHIDTL_ROOTLINE|HHIDTL_ICON);

	void SetListTitle(CString strTitle);
	void SetHeadFont(CString strFont, int nSize, BOOL bBold, BOOL bItalic);
	void SetChnFont(CString strFont, int nSize, BOOL bBold, BOOL bItalic);
	void SetNumFont(CString strFont, int nSize, BOOL bBold, BOOL bItalic);
	void SetHeadColor(COLORREF colorFr, COLORREF colorBk, COLORREF colorBk1);
	void SetListLineColor(COLORREF colorVLine,COLORREF colorHLine);
	void SetListColor(COLORREF colorFr, COLORREF colorBk, COLORREF colorBk1);
	void SetCursorColor(COLORREF colorCur, COLORREF colorCurBk, COLORREF colorCurBk1);
	void SetLineSpace(int nLintSpace);		//�����м��
	void SetListSet(HHLISTSET_FONT *pFont, HHLISTSET_COLOR *pColor, HHLISTSET_SET *pSet);
	void SetCursorType(BOOL bCursorY, BOOL bCursorX);

	void GetListRect(RECT &rect, BOOL bSplit=FALSE);
	void GetItemRect(int nID, int record, RECT &rect, BOOL bSplit=FALSE);
	int  GetRecordFromPoint(CPoint point);
	int  GetHeadIndexFromPoint(CPoint point);
	int  GetCursorLine();
	int  SetCursorLine(int nCursorY, int nCursorX=-1, BOOL bRedraw=TRUE);
	int  GetFirstLine();
	int  SetFirstLine(int nLine);
	int  SetLockCols(int nLocks);
	void SetScroll(int bHScroll, int bVScroll);
	void SetMultiSelect(int nFirst, int nLast);
	BOOL ClearMultiSelect();
	virtual void OnChangedMultiSelect();
	int	 EnableMultiSelect(BOOL bMulit=TRUE);
	int	 GetMultiSelectFlag(int nRecord);
	void EnableCursor(BOOL bEnable=TRUE);
	void KeyInputProc(UINT nChar);
	void ReFlashList(int flag=1);
	void ReFlash();
	void SetHHScrollDrawStyle(int nDrawStyle);
	void SetHHScrollColorSet(HHFC_HHSCROLLCOLORSET *pcolorSet);
	void SetActive(BOOL bActive, BOOL bRedraw=TRUE);
	int  GetColMaxWidth(int nSplit, int nCol);

	void CopyDataToClipboard(int nBegin, int nEnd);
public:
	//��д����
	virtual void OnBeforeDrawList();		//�б����ǰ
	virtual void OnAfterDrawList();			//�б������Ϻ�
	
	virtual LRESULT OnHHProcessor(WPARAM wParam, LPARAM lParam);
	///
	virtual int  OnGetOwnerItemCtrlWidth(int nSplit, int nCol);
	//���б�
	virtual int  OnGetListHeadColumeInfo(int nIndex, char *pDataInfo, int *pnWidth, int *pnTa, int *pnSort, int nPaintFlag=1);
	virtual int  OnGetListHeadColumeDefaultWidth(int nIndex, int nWidth);
	virtual int  OnSetListHeadColumeWidth(int nIndex, int nWidth);
	virtual int  OnSetListHeadSort(int nIndex);
	virtual int  OnGetListItemInfo(int nIndex, int record, BOOL bCursor,char *pDataInfo, COLORREF *colorFr, COLORREF *colorBk, COLORREF *colorBk1, int *sFlag=NULL, COLORREF *colorFlag=NULL, int flag=0);
	virtual int  OnAdjustHeadOrder(int nOld, int nNew);
	virtual void OnAfterDrawListLine(CDC *pDC, int record, BOOL bCursor, int nPaintFlag, RECT rectLine);//���������

	//�Զ������Head(OnGetListHeadColumeInfo����ֵ0x0fffffff)
	virtual void OnDrawOwnerHeadColume(CDC *pDC, RECT rect, int nIndex, char *pDataInfo, int nWidth, int nTa, int nSort, int nPaintFlag);
	//�Զ������Item(OnGetListItemInfo����ֵ0x0fffffff)
	virtual void OnDrawOwnerItem(CDC *pDC, RECT rect, int nIndex, int record, BOOL bCursor,char *pDataInfo, COLORREF colorFr, COLORREF colorBk, COLORREF colorBk1, int sFlag, COLORREF colorFlag, int flag);
	//�Զ������Ctrl(OnGetListItemInfo����ֵ0x0ffffff0)
	virtual void OnDrawOwnerCtrlItem(RECT rect, int nIndex, int record, BOOL bCursor);
	//�ָ��б�
	virtual int  OnGetListHeadColumeInfoSplit(int nIndex, char *pDataInfo, int *pnWidth, int *pnTa, int *pnSort, int nPaintFlag=1);
	virtual int  OnGetListHeadColumeDefaultWidthSplit(int nIndex, int nWidth);
	virtual int  OnSetListHeadColumeWidthSplit(int nIndex, int nWidth);
	virtual int  OnSetListHeadSortSplit(int nIndex);
	virtual int  OnGetListItemInfoSplit(int nIndex, int record, BOOL bCursor,char *pDataInfo, COLORREF *colorFr, COLORREF *colorBk, COLORREF *colorBk1, int *sFlag=NULL, COLORREF *colorFlag=NULL, int flag=0);
	virtual int  OnAdjustHeadOrderSplit(int nOld, int nNew);
	//�Զ������Head(OnGetListHeadColumeInfoSplit����ֵ0x0fffffff)
	virtual void OnDrawOwnerHeadColumeSplit(CDC *pDC, RECT rect, int nIndex, char *pDataInfo, int nWidth, int nTa, int nSort, int nPaintFlag);
	//�Զ������Item(OnGetListItemInfoSplit����ֵ0x0fffffff)
	virtual void OnDrawOwnerItemSplit(CDC *pDC, RECT rect, int nIndex, int record, BOOL bCursor,char *pDataInfo, COLORREF colorFr, COLORREF colorBk, COLORREF colorBk1, int sFlag, COLORREF colorFlag, int flag);
	//�Զ������Ctrl(OnGetListItemInfo����ֵ0x0ffffff0)
	virtual void OnDrawOwnerCtrlItemSplit(RECT rect, int nIndex, int record, BOOL bCursor);
	//����
	virtual void OnDrawTitle(CDC *pDC);
	//
	virtual int  OnLButtonDblClkOnListRecord(int nRecord);
	virtual int  OnPrepareRlash(int mode);
	virtual int  OnChangeInput(char *strInput, int nKey);
	virtual void OnGetListRectPos(CDC *pDC, RECT &rect);
	virtual void OnUpdateNoListRect(CDC *pDC);
	//����ˮƽ��������λ��
	virtual BOOL OnSetVScrollPos(RECT &rect, int nSpli);
	virtual int  OnSetListColWidthToMaxItemWidth(int nSplit, int nCol, int nWidth);
	virtual void OnChangedSelectItem(int oldItem, int newItem, int nSplit, int oldCol, int newCol);
	//��������Ϣ(����CHHView)
	virtual BOOL MouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//��Ǳ�ͷ��Ŀ
	int MarkListHeadItem(CPoint point, int nSplit=0, COLORREF colorFr=RGB(255,0,0), COLORREF colorBk1=RGB(255,255,255), COLORREF colorBk2=RGB(255,255,255), int dwFlag=0);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
};
