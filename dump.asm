
build/uspace/apps/hello/hello.elf:     file format elf64-littleriscv


Disassembly of section .text:

0000000012000000 <main>:
    12000000:	1141                	addi	sp,sp,-16
    12000002:	00001517          	auipc	a0,0x1
    12000006:	ffe50513          	addi	a0,a0,-2 # 12001000 <__srodata>
    1200000a:	e022                	sd	s0,0(sp)
    1200000c:	e406                	sd	ra,8(sp)
    1200000e:	00002417          	auipc	s0,0x2
    12000012:	0f240413          	addi	s0,s0,242 # 12002100 <counter>
    12000016:	00000097          	auipc	ra,0x0
    1200001a:	57c080e7          	jalr	1404(ra) # 12000592 <printf>
    1200001e:	600c                	ld	a1,0(s0)
    12000020:	00001517          	auipc	a0,0x1
    12000024:	00050513          	mv	a0,a0
    12000028:	00158793          	addi	a5,a1,1
    1200002c:	e01c                	sd	a5,0(s0)
    1200002e:	00000097          	auipc	ra,0x0
    12000032:	564080e7          	jalr	1380(ra) # 12000592 <printf>
    12000036:	00000097          	auipc	ra,0x0
    1200003a:	60e080e7          	jalr	1550(ra) # 12000644 <task_yield>
    1200003e:	b7c5                	j	1200001e <main+0x1e>

0000000012000040 <putc.isra.0>:
    12000040:	00002797          	auipc	a5,0x2
    12000044:	0c87b783          	ld	a5,200(a5) # 12002108 <buf_index>
    12000048:	1101                	addi	sp,sp,-32
    1200004a:	ec06                	sd	ra,24(sp)
    1200004c:	0fe00693          	li	a3,254
    12000050:	872a                	mv	a4,a0
    12000052:	02f6e563          	bltu	a3,a5,1200007c <putc.isra.0+0x3c>
    12000056:	00178613          	addi	a2,a5,1
    1200005a:	00002697          	auipc	a3,0x2
    1200005e:	fa668693          	addi	a3,a3,-90 # 12002000 <buf>
    12000062:	97b6                	add	a5,a5,a3
    12000064:	00e78023          	sb	a4,0(a5)
    12000068:	00002797          	auipc	a5,0x2
    1200006c:	0ac7b023          	sd	a2,160(a5) # 12002108 <buf_index>
    12000070:	47a9                	li	a5,10
    12000072:	02f70863          	beq	a4,a5,120000a2 <putc.isra.0+0x62>
    12000076:	60e2                	ld	ra,24(sp)
    12000078:	6105                	addi	sp,sp,32
    1200007a:	8082                	ret
    1200007c:	00002697          	auipc	a3,0x2
    12000080:	f8468693          	addi	a3,a3,-124 # 12002000 <buf>
    12000084:	97b6                	add	a5,a5,a3
    12000086:	e42a                	sd	a0,8(sp)
    12000088:	8536                	mv	a0,a3
    1200008a:	00078023          	sb	zero,0(a5)
    1200008e:	e036                	sd	a3,0(sp)
    12000090:	00000097          	auipc	ra,0x0
    12000094:	52a080e7          	jalr	1322(ra) # 120005ba <__puts>
    12000098:	6722                	ld	a4,8(sp)
    1200009a:	6682                	ld	a3,0(sp)
    1200009c:	4605                	li	a2,1
    1200009e:	4781                	li	a5,0
    120000a0:	b7c9                	j	12000062 <putc.isra.0+0x22>
    120000a2:	96b2                	add	a3,a3,a2
    120000a4:	00002517          	auipc	a0,0x2
    120000a8:	f5c50513          	addi	a0,a0,-164 # 12002000 <buf>
    120000ac:	00068023          	sb	zero,0(a3)
    120000b0:	00000097          	auipc	ra,0x0
    120000b4:	50a080e7          	jalr	1290(ra) # 120005ba <__puts>
    120000b8:	00002797          	auipc	a5,0x2
    120000bc:	0407b823          	sd	zero,80(a5) # 12002108 <buf_index>
    120000c0:	bf5d                	j	12000076 <putc.isra.0+0x36>

00000000120000c2 <print_int>:
    120000c2:	7171                	addi	sp,sp,-176
    120000c4:	f506                	sd	ra,168(sp)
    120000c6:	87aa                	mv	a5,a0
    120000c8:	12055863          	bgez	a0,120001f8 <print_int+0x136>
    120000cc:	12060663          	beqz	a2,120001f8 <print_int+0x136>
    120000d0:	f122                	sd	s0,160(sp)
    120000d2:	ed26                	sd	s1,152(sp)
    120000d4:	e94a                	sd	s2,144(sp)
    120000d6:	e54e                	sd	s3,136(sp)
    120000d8:	40a007b3          	neg	a5,a0
    120000dc:	02d00893          	li	a7,45
    120000e0:	fc02                	sd	zero,56(sp)
    120000e2:	e082                	sd	zero,64(sp)
    120000e4:	e482                	sd	zero,72(sp)
    120000e6:	e882                	sd	zero,80(sp)
    120000e8:	ec82                	sd	zero,88(sp)
    120000ea:	f082                	sd	zero,96(sp)
    120000ec:	f482                	sd	zero,104(sp)
    120000ee:	f882                	sd	zero,112(sp)
    120000f0:	06010c23          	sb	zero,120(sp)
    120000f4:	4401                	li	s0,0
    120000f6:	1824                	addi	s1,sp,56
    120000f8:	00001817          	auipc	a6,0x1
    120000fc:	f4080813          	addi	a6,a6,-192 # 12001038 <__srodata+0x38>
    12000100:	02b7f733          	remu	a4,a5,a1
    12000104:	8922                	mv	s2,s0
    12000106:	0405                	addi	s0,s0,1
    12000108:	00848533          	add	a0,s1,s0
    1200010c:	863e                	mv	a2,a5
    1200010e:	9742                	add	a4,a4,a6
    12000110:	00074703          	lbu	a4,0(a4)
    12000114:	02b7d7b3          	divu	a5,a5,a1
    12000118:	fee50fa3          	sb	a4,-1(a0)
    1200011c:	feb672e3          	bgeu	a2,a1,12000100 <print_int+0x3e>
    12000120:	0e089563          	bnez	a7,1200020a <print_int+0x148>
    12000124:	01043793          	sltiu	a5,s0,16
    12000128:	cff9                	beqz	a5,12000206 <print_int+0x144>
    1200012a:	cef1                	beqz	a3,12000206 <print_int+0x144>
    1200012c:	00002597          	auipc	a1,0x2
    12000130:	fdc58593          	addi	a1,a1,-36 # 12002108 <buf_index>
    12000134:	6198                	ld	a4,0(a1)
    12000136:	8ea2                	mv	t4,s0
    12000138:	00002617          	auipc	a2,0x2
    1200013c:	ec860613          	addi	a2,a2,-312 # 12002000 <buf>
    12000140:	4841                	li	a6,16
    12000142:	41d8083b          	subw	a6,a6,t4
    12000146:	4681                	li	a3,0
    12000148:	0fe00313          	li	t1,254
    1200014c:	03000e13          	li	t3,48
    12000150:	a819                	j	12000166 <print_int+0xa4>
    12000152:	87ba                	mv	a5,a4
    12000154:	00178713          	addi	a4,a5,1
    12000158:	97b2                	add	a5,a5,a2
    1200015a:	2685                	addiw	a3,a3,1
    1200015c:	e198                	sd	a4,0(a1)
    1200015e:	01c78023          	sb	t3,0(a5)
    12000162:	07068063          	beq	a3,a6,120001c2 <print_int+0x100>
    12000166:	00e607b3          	add	a5,a2,a4
    1200016a:	00002517          	auipc	a0,0x2
    1200016e:	e9650513          	addi	a0,a0,-362 # 12002000 <buf>
    12000172:	fee370e3          	bgeu	t1,a4,12000152 <print_int+0x90>
    12000176:	f432                	sd	a2,40(sp)
    12000178:	f02e                	sd	a1,32(sp)
    1200017a:	ec42                	sd	a6,24(sp)
    1200017c:	e836                	sd	a3,16(sp)
    1200017e:	e476                	sd	t4,8(sp)
    12000180:	e046                	sd	a7,0(sp)
    12000182:	00078023          	sb	zero,0(a5)
    12000186:	00000097          	auipc	ra,0x0
    1200018a:	434080e7          	jalr	1076(ra) # 120005ba <__puts>
    1200018e:	7582                	ld	a1,32(sp)
    12000190:	7622                	ld	a2,40(sp)
    12000192:	66c2                	ld	a3,16(sp)
    12000194:	6862                	ld	a6,24(sp)
    12000196:	4785                	li	a5,1
    12000198:	03000713          	li	a4,48
    1200019c:	e19c                	sd	a5,0(a1)
    1200019e:	00e60023          	sb	a4,0(a2)
    120001a2:	0016851b          	addiw	a0,a3,1
    120001a6:	6882                	ld	a7,0(sp)
    120001a8:	6ea2                	ld	t4,8(sp)
    120001aa:	4789                	li	a5,2
    120001ac:	01050b63          	beq	a0,a6,120001c2 <print_int+0x100>
    120001b0:	e19c                	sd	a5,0(a1)
    120001b2:	00e600a3          	sb	a4,1(a2)
    120001b6:	2689                	addiw	a3,a3,2
    120001b8:	0fe00313          	li	t1,254
    120001bc:	8e3a                	mv	t3,a4
    120001be:	f8d81be3          	bne	a6,a3,12000154 <print_int+0x92>
    120001c2:	41d887bb          	subw	a5,a7,t4
    120001c6:	0107899b          	addiw	s3,a5,16
    120001ca:	008487b3          	add	a5,s1,s0
    120001ce:	fff7c503          	lbu	a0,-1(a5)
    120001d2:	147d                	addi	s0,s0,-1
    120001d4:	00000097          	auipc	ra,0x0
    120001d8:	e6c080e7          	jalr	-404(ra) # 12000040 <putc.isra.0>
    120001dc:	f47d                	bnez	s0,120001ca <print_int+0x108>
    120001de:	740a                	ld	s0,160(sp)
    120001e0:	70aa                	ld	ra,168(sp)
    120001e2:	0019051b          	addiw	a0,s2,1
    120001e6:	0135053b          	addw	a0,a0,s3
    120001ea:	1502                	slli	a0,a0,0x20
    120001ec:	64ea                	ld	s1,152(sp)
    120001ee:	694a                	ld	s2,144(sp)
    120001f0:	69aa                	ld	s3,136(sp)
    120001f2:	9101                	srli	a0,a0,0x20
    120001f4:	614d                	addi	sp,sp,176
    120001f6:	8082                	ret
    120001f8:	4881                	li	a7,0
    120001fa:	c539                	beqz	a0,12000248 <print_int+0x186>
    120001fc:	f122                	sd	s0,160(sp)
    120001fe:	ed26                	sd	s1,152(sp)
    12000200:	e94a                	sd	s2,144(sp)
    12000202:	e54e                	sd	s3,136(sp)
    12000204:	bdf1                	j	120000e0 <print_int+0x1e>
    12000206:	4981                	li	s3,0
    12000208:	b7c9                	j	120001ca <print_int+0x108>
    1200020a:	00002597          	auipc	a1,0x2
    1200020e:	efe58593          	addi	a1,a1,-258 # 12002108 <buf_index>
    12000212:	619c                	ld	a5,0(a1)
    12000214:	0fe00713          	li	a4,254
    12000218:	00290e93          	addi	t4,s2,2
    1200021c:	06f76163          	bltu	a4,a5,1200027e <print_int+0x1bc>
    12000220:	00178713          	addi	a4,a5,1
    12000224:	00002617          	auipc	a2,0x2
    12000228:	ddc60613          	addi	a2,a2,-548 # 12002000 <buf>
    1200022c:	97b2                	add	a5,a5,a2
    1200022e:	02d00513          	li	a0,45
    12000232:	00a78023          	sb	a0,0(a5)
    12000236:	e198                	sd	a4,0(a1)
    12000238:	010eb793          	sltiu	a5,t4,16
    1200023c:	c781                	beqz	a5,12000244 <print_int+0x182>
    1200023e:	c299                	beqz	a3,12000244 <print_int+0x182>
    12000240:	4885                	li	a7,1
    12000242:	bdfd                	j	12000140 <print_int+0x7e>
    12000244:	4985                	li	s3,1
    12000246:	b751                	j	120001ca <print_int+0x108>
    12000248:	00002797          	auipc	a5,0x2
    1200024c:	ec07b783          	ld	a5,-320(a5) # 12002108 <buf_index>
    12000250:	0fe00713          	li	a4,254
    12000254:	04f76c63          	bltu	a4,a5,120002ac <print_int+0x1ea>
    12000258:	00178693          	addi	a3,a5,1
    1200025c:	00002617          	auipc	a2,0x2
    12000260:	da460613          	addi	a2,a2,-604 # 12002000 <buf>
    12000264:	97b2                	add	a5,a5,a2
    12000266:	03000713          	li	a4,48
    1200026a:	00e78023          	sb	a4,0(a5)
    1200026e:	70aa                	ld	ra,168(sp)
    12000270:	00002617          	auipc	a2,0x2
    12000274:	e8d63c23          	sd	a3,-360(a2) # 12002108 <buf_index>
    12000278:	4505                	li	a0,1
    1200027a:	614d                	addi	sp,sp,176
    1200027c:	8082                	ret
    1200027e:	00002617          	auipc	a2,0x2
    12000282:	d8260613          	addi	a2,a2,-638 # 12002000 <buf>
    12000286:	97b2                	add	a5,a5,a2
    12000288:	8532                	mv	a0,a2
    1200028a:	ec36                	sd	a3,24(sp)
    1200028c:	e82e                	sd	a1,16(sp)
    1200028e:	e476                	sd	t4,8(sp)
    12000290:	00078023          	sb	zero,0(a5)
    12000294:	e032                	sd	a2,0(sp)
    12000296:	00000097          	auipc	ra,0x0
    1200029a:	324080e7          	jalr	804(ra) # 120005ba <__puts>
    1200029e:	66e2                	ld	a3,24(sp)
    120002a0:	65c2                	ld	a1,16(sp)
    120002a2:	6ea2                	ld	t4,8(sp)
    120002a4:	6602                	ld	a2,0(sp)
    120002a6:	4705                	li	a4,1
    120002a8:	4781                	li	a5,0
    120002aa:	b749                	j	1200022c <print_int+0x16a>
    120002ac:	00002617          	auipc	a2,0x2
    120002b0:	d5460613          	addi	a2,a2,-684 # 12002000 <buf>
    120002b4:	97b2                	add	a5,a5,a2
    120002b6:	8532                	mv	a0,a2
    120002b8:	00078023          	sb	zero,0(a5)
    120002bc:	e032                	sd	a2,0(sp)
    120002be:	00000097          	auipc	ra,0x0
    120002c2:	2fc080e7          	jalr	764(ra) # 120005ba <__puts>
    120002c6:	6602                	ld	a2,0(sp)
    120002c8:	4685                	li	a3,1
    120002ca:	4781                	li	a5,0
    120002cc:	bf61                	j	12000264 <print_int+0x1a2>

00000000120002ce <vprintf>:
    120002ce:	711d                	addi	sp,sp,-96
    120002d0:	e4a6                	sd	s1,72(sp)
    120002d2:	ec86                	sd	ra,88(sp)
    120002d4:	e8a2                	sd	s0,80(sp)
    120002d6:	ec5e                	sd	s7,24(sp)
    120002d8:	84aa                	mv	s1,a0
    120002da:	00054503          	lbu	a0,0(a0)
    120002de:	22050b63          	beqz	a0,12000514 <vprintf+0x246>
    120002e2:	e0ca                	sd	s2,64(sp)
    120002e4:	fc4e                	sd	s3,56(sp)
    120002e6:	f456                	sd	s5,40(sp)
    120002e8:	f05a                	sd	s6,32(sp)
    120002ea:	e862                	sd	s8,16(sp)
    120002ec:	f852                	sd	s4,48(sp)
    120002ee:	892e                	mv	s2,a1
    120002f0:	4c01                	li	s8,0
    120002f2:	4401                	li	s0,0
    120002f4:	00002b97          	auipc	s7,0x2
    120002f8:	e14b8b93          	addi	s7,s7,-492 # 12002108 <buf_index>
    120002fc:	02500993          	li	s3,37
    12000300:	4b59                	li	s6,22
    12000302:	00001a97          	auipc	s5,0x1
    12000306:	db6a8a93          	addi	s5,s5,-586 # 120010b8 <__srodata+0xb8>
    1200030a:	03351563          	bne	a0,s3,12000334 <vprintf+0x66>
    1200030e:	001c0a13          	addi	s4,s8,1
    12000312:	014487b3          	add	a5,s1,s4
    12000316:	0007c783          	lbu	a5,0(a5)
    1200031a:	19378563          	beq	a5,s3,120004a4 <vprintf+0x1d6>
    1200031e:	f9e7879b          	addiw	a5,a5,-98
    12000322:	0ff7f793          	zext.b	a5,a5
    12000326:	04fb6363          	bltu	s6,a5,1200036c <vprintf+0x9e>
    1200032a:	078a                	slli	a5,a5,0x2
    1200032c:	97d6                	add	a5,a5,s5
    1200032e:	439c                	lw	a5,0(a5)
    12000330:	97d6                	add	a5,a5,s5
    12000332:	8782                	jr	a5
    12000334:	00000097          	auipc	ra,0x0
    12000338:	d0c080e7          	jalr	-756(ra) # 12000040 <putc.isra.0>
    1200033c:	0405                	addi	s0,s0,1
    1200033e:	0c05                	addi	s8,s8,1
    12000340:	018487b3          	add	a5,s1,s8
    12000344:	0007c503          	lbu	a0,0(a5)
    12000348:	f169                	bnez	a0,1200030a <vprintf+0x3c>
    1200034a:	6906                	ld	s2,64(sp)
    1200034c:	79e2                	ld	s3,56(sp)
    1200034e:	7a42                	ld	s4,48(sp)
    12000350:	7aa2                	ld	s5,40(sp)
    12000352:	7b02                	ld	s6,32(sp)
    12000354:	6c42                	ld	s8,16(sp)
    12000356:	000bb783          	ld	a5,0(s7)
    1200035a:	16079b63          	bnez	a5,120004d0 <vprintf+0x202>
    1200035e:	60e6                	ld	ra,88(sp)
    12000360:	8522                	mv	a0,s0
    12000362:	6446                	ld	s0,80(sp)
    12000364:	64a6                	ld	s1,72(sp)
    12000366:	6be2                	ld	s7,24(sp)
    12000368:	6125                	addi	sp,sp,96
    1200036a:	8082                	ret
    1200036c:	00001517          	auipc	a0,0x1
    12000370:	d1c50513          	addi	a0,a0,-740 # 12001088 <__srodata+0x88>
    12000374:	00000097          	auipc	ra,0x0
    12000378:	26e080e7          	jalr	622(ra) # 120005e2 <__panic>
    1200037c:	8c52                	mv	s8,s4
    1200037e:	b7c1                	j	1200033e <vprintf+0x70>
    12000380:	00096503          	lwu	a0,0(s2)
    12000384:	4681                	li	a3,0
    12000386:	4601                	li	a2,0
    12000388:	45c1                	li	a1,16
    1200038a:	00000097          	auipc	ra,0x0
    1200038e:	d38080e7          	jalr	-712(ra) # 120000c2 <print_int>
    12000392:	0921                	addi	s2,s2,8
    12000394:	8c52                	mv	s8,s4
    12000396:	942a                	add	s0,s0,a0
    12000398:	b75d                	j	1200033e <vprintf+0x70>
    1200039a:	e466                	sd	s9,8(sp)
    1200039c:	00093c83          	ld	s9,0(s2)
    120003a0:	0921                	addi	s2,s2,8
    120003a2:	1e0c9263          	bnez	s9,12000586 <vprintf+0x2b8>
    120003a6:	00001c97          	auipc	s9,0x1
    120003aa:	caac8c93          	addi	s9,s9,-854 # 12001050 <__srodata+0x50>
    120003ae:	02800513          	li	a0,40
    120003b2:	4c01                	li	s8,0
    120003b4:	00000097          	auipc	ra,0x0
    120003b8:	c8c080e7          	jalr	-884(ra) # 12000040 <putc.isra.0>
    120003bc:	0c05                	addi	s8,s8,1
    120003be:	018c87b3          	add	a5,s9,s8
    120003c2:	0007c503          	lbu	a0,0(a5)
    120003c6:	f57d                	bnez	a0,120003b4 <vprintf+0xe6>
    120003c8:	9462                	add	s0,s0,s8
    120003ca:	6ca2                	ld	s9,8(sp)
    120003cc:	8c52                	mv	s8,s4
    120003ce:	bf85                	j	1200033e <vprintf+0x70>
    120003d0:	03000513          	li	a0,48
    120003d4:	00093c03          	ld	s8,0(s2)
    120003d8:	00000097          	auipc	ra,0x0
    120003dc:	c68080e7          	jalr	-920(ra) # 12000040 <putc.isra.0>
    120003e0:	07800513          	li	a0,120
    120003e4:	00000097          	auipc	ra,0x0
    120003e8:	c5c080e7          	jalr	-932(ra) # 12000040 <putc.isra.0>
    120003ec:	8562                	mv	a0,s8
    120003ee:	4685                	li	a3,1
    120003f0:	4601                	li	a2,0
    120003f2:	45c1                	li	a1,16
    120003f4:	00000097          	auipc	ra,0x0
    120003f8:	cce080e7          	jalr	-818(ra) # 120000c2 <print_int>
    120003fc:	0409                	addi	s0,s0,2
    120003fe:	0921                	addi	s2,s2,8
    12000400:	8c52                	mv	s8,s4
    12000402:	942a                	add	s0,s0,a0
    12000404:	bf2d                	j	1200033e <vprintf+0x70>
    12000406:	00096503          	lwu	a0,0(s2)
    1200040a:	4681                	li	a3,0
    1200040c:	4601                	li	a2,0
    1200040e:	45a1                	li	a1,8
    12000410:	00000097          	auipc	ra,0x0
    12000414:	cb2080e7          	jalr	-846(ra) # 120000c2 <print_int>
    12000418:	0921                	addi	s2,s2,8
    1200041a:	8c52                	mv	s8,s4
    1200041c:	942a                	add	s0,s0,a0
    1200041e:	b705                	j	1200033e <vprintf+0x70>
    12000420:	0c09                	addi	s8,s8,2
    12000422:	018487b3          	add	a5,s1,s8
    12000426:	0007c783          	lbu	a5,0(a5)
    1200042a:	06400713          	li	a4,100
    1200042e:	0ee78963          	beq	a5,a4,12000520 <vprintf+0x252>
    12000432:	07800713          	li	a4,120
    12000436:	10e78163          	beq	a5,a4,12000538 <vprintf+0x26a>
    1200043a:	06200713          	li	a4,98
    1200043e:	10e78963          	beq	a5,a4,12000550 <vprintf+0x282>
    12000442:	06f00713          	li	a4,111
    12000446:	0ae78b63          	beq	a5,a4,120004fc <vprintf+0x22e>
    1200044a:	00001517          	auipc	a0,0x1
    1200044e:	c0e50513          	addi	a0,a0,-1010 # 12001058 <__srodata+0x58>
    12000452:	00000097          	auipc	ra,0x0
    12000456:	190080e7          	jalr	400(ra) # 120005e2 <__panic>
    1200045a:	b5d5                	j	1200033e <vprintf+0x70>
    1200045c:	00092503          	lw	a0,0(s2)
    12000460:	4681                	li	a3,0
    12000462:	4605                	li	a2,1
    12000464:	45a9                	li	a1,10
    12000466:	00000097          	auipc	ra,0x0
    1200046a:	c5c080e7          	jalr	-932(ra) # 120000c2 <print_int>
    1200046e:	0921                	addi	s2,s2,8
    12000470:	8c52                	mv	s8,s4
    12000472:	942a                	add	s0,s0,a0
    12000474:	b5e9                	j	1200033e <vprintf+0x70>
    12000476:	00094503          	lbu	a0,0(s2)
    1200047a:	0405                	addi	s0,s0,1
    1200047c:	0921                	addi	s2,s2,8
    1200047e:	00000097          	auipc	ra,0x0
    12000482:	bc2080e7          	jalr	-1086(ra) # 12000040 <putc.isra.0>
    12000486:	8c52                	mv	s8,s4
    12000488:	bd5d                	j	1200033e <vprintf+0x70>
    1200048a:	00096503          	lwu	a0,0(s2)
    1200048e:	4681                	li	a3,0
    12000490:	4601                	li	a2,0
    12000492:	4589                	li	a1,2
    12000494:	00000097          	auipc	ra,0x0
    12000498:	c2e080e7          	jalr	-978(ra) # 120000c2 <print_int>
    1200049c:	0921                	addi	s2,s2,8
    1200049e:	8c52                	mv	s8,s4
    120004a0:	942a                	add	s0,s0,a0
    120004a2:	bd71                	j	1200033e <vprintf+0x70>
    120004a4:	000bb783          	ld	a5,0(s7)
    120004a8:	0fe00713          	li	a4,254
    120004ac:	0af76e63          	bltu	a4,a5,12000568 <vprintf+0x29a>
    120004b0:	00178693          	addi	a3,a5,1
    120004b4:	00002c17          	auipc	s8,0x2
    120004b8:	b4cc0c13          	addi	s8,s8,-1204 # 12002000 <buf>
    120004bc:	97e2                	add	a5,a5,s8
    120004be:	02500713          	li	a4,37
    120004c2:	00dbb023          	sd	a3,0(s7)
    120004c6:	0405                	addi	s0,s0,1
    120004c8:	8c52                	mv	s8,s4
    120004ca:	00e78023          	sb	a4,0(a5)
    120004ce:	bd85                	j	1200033e <vprintf+0x70>
    120004d0:	00002517          	auipc	a0,0x2
    120004d4:	b3050513          	addi	a0,a0,-1232 # 12002000 <buf>
    120004d8:	97aa                	add	a5,a5,a0
    120004da:	00078023          	sb	zero,0(a5)
    120004de:	00000097          	auipc	ra,0x0
    120004e2:	0dc080e7          	jalr	220(ra) # 120005ba <__puts>
    120004e6:	60e6                	ld	ra,88(sp)
    120004e8:	8522                	mv	a0,s0
    120004ea:	6446                	ld	s0,80(sp)
    120004ec:	00002797          	auipc	a5,0x2
    120004f0:	c007be23          	sd	zero,-996(a5) # 12002108 <buf_index>
    120004f4:	64a6                	ld	s1,72(sp)
    120004f6:	6be2                	ld	s7,24(sp)
    120004f8:	6125                	addi	sp,sp,96
    120004fa:	8082                	ret
    120004fc:	00093503          	ld	a0,0(s2)
    12000500:	4681                	li	a3,0
    12000502:	4601                	li	a2,0
    12000504:	45a1                	li	a1,8
    12000506:	00000097          	auipc	ra,0x0
    1200050a:	bbc080e7          	jalr	-1092(ra) # 120000c2 <print_int>
    1200050e:	0921                	addi	s2,s2,8
    12000510:	942a                	add	s0,s0,a0
    12000512:	b535                	j	1200033e <vprintf+0x70>
    12000514:	4401                	li	s0,0
    12000516:	00002b97          	auipc	s7,0x2
    1200051a:	bf2b8b93          	addi	s7,s7,-1038 # 12002108 <buf_index>
    1200051e:	bd25                	j	12000356 <vprintf+0x88>
    12000520:	00093503          	ld	a0,0(s2)
    12000524:	4681                	li	a3,0
    12000526:	4605                	li	a2,1
    12000528:	45a9                	li	a1,10
    1200052a:	00000097          	auipc	ra,0x0
    1200052e:	b98080e7          	jalr	-1128(ra) # 120000c2 <print_int>
    12000532:	0921                	addi	s2,s2,8
    12000534:	942a                	add	s0,s0,a0
    12000536:	b521                	j	1200033e <vprintf+0x70>
    12000538:	00093503          	ld	a0,0(s2)
    1200053c:	4681                	li	a3,0
    1200053e:	4601                	li	a2,0
    12000540:	45c1                	li	a1,16
    12000542:	00000097          	auipc	ra,0x0
    12000546:	b80080e7          	jalr	-1152(ra) # 120000c2 <print_int>
    1200054a:	0921                	addi	s2,s2,8
    1200054c:	942a                	add	s0,s0,a0
    1200054e:	bbc5                	j	1200033e <vprintf+0x70>
    12000550:	00093503          	ld	a0,0(s2)
    12000554:	4681                	li	a3,0
    12000556:	4601                	li	a2,0
    12000558:	4589                	li	a1,2
    1200055a:	00000097          	auipc	ra,0x0
    1200055e:	b68080e7          	jalr	-1176(ra) # 120000c2 <print_int>
    12000562:	0921                	addi	s2,s2,8
    12000564:	942a                	add	s0,s0,a0
    12000566:	bbe1                	j	1200033e <vprintf+0x70>
    12000568:	00002c17          	auipc	s8,0x2
    1200056c:	a98c0c13          	addi	s8,s8,-1384 # 12002000 <buf>
    12000570:	97e2                	add	a5,a5,s8
    12000572:	8562                	mv	a0,s8
    12000574:	00078023          	sb	zero,0(a5)
    12000578:	00000097          	auipc	ra,0x0
    1200057c:	042080e7          	jalr	66(ra) # 120005ba <__puts>
    12000580:	4685                	li	a3,1
    12000582:	4781                	li	a5,0
    12000584:	bf25                	j	120004bc <vprintf+0x1ee>
    12000586:	000cc503          	lbu	a0,0(s9)
    1200058a:	4c01                	li	s8,0
    1200058c:	e2050ee3          	beqz	a0,120003c8 <vprintf+0xfa>
    12000590:	b50d                	j	120003b2 <vprintf+0xe4>

0000000012000592 <printf>:
    12000592:	711d                	addi	sp,sp,-96
    12000594:	02810313          	addi	t1,sp,40
    12000598:	f42e                	sd	a1,40(sp)
    1200059a:	859a                	mv	a1,t1
    1200059c:	ec06                	sd	ra,24(sp)
    1200059e:	f832                	sd	a2,48(sp)
    120005a0:	fc36                	sd	a3,56(sp)
    120005a2:	e0ba                	sd	a4,64(sp)
    120005a4:	e4be                	sd	a5,72(sp)
    120005a6:	e8c2                	sd	a6,80(sp)
    120005a8:	ecc6                	sd	a7,88(sp)
    120005aa:	e41a                	sd	t1,8(sp)
    120005ac:	00000097          	auipc	ra,0x0
    120005b0:	d22080e7          	jalr	-734(ra) # 120002ce <vprintf>
    120005b4:	60e2                	ld	ra,24(sp)
    120005b6:	6125                	addi	sp,sp,96
    120005b8:	8082                	ret

00000000120005ba <__puts>:
    120005ba:	1141                	addi	sp,sp,-16
    120005bc:	e022                	sd	s0,0(sp)
    120005be:	e406                	sd	ra,8(sp)
    120005c0:	842a                	mv	s0,a0
    120005c2:	00000097          	auipc	ra,0x0
    120005c6:	134080e7          	jalr	308(ra) # 120006f6 <strlen>
    120005ca:	85aa                	mv	a1,a0
    120005cc:	4601                	li	a2,0
    120005ce:	8522                	mv	a0,s0
    120005d0:	4681                	li	a3,0
    120005d2:	4701                	li	a4,0
    120005d4:	4889                	li	a7,2
    120005d6:	00000073          	ecall
    120005da:	60a2                	ld	ra,8(sp)
    120005dc:	6402                	ld	s0,0(sp)
    120005de:	0141                	addi	sp,sp,16
    120005e0:	8082                	ret

00000000120005e2 <__panic>:
    120005e2:	711d                	addi	sp,sp,-96
    120005e4:	02810313          	addi	t1,sp,40
    120005e8:	e822                	sd	s0,16(sp)
    120005ea:	842a                	mv	s0,a0
    120005ec:	00001517          	auipc	a0,0x1
    120005f0:	ac450513          	addi	a0,a0,-1340 # 120010b0 <__srodata+0xb0>
    120005f4:	ec06                	sd	ra,24(sp)
    120005f6:	f42e                	sd	a1,40(sp)
    120005f8:	f832                	sd	a2,48(sp)
    120005fa:	fc36                	sd	a3,56(sp)
    120005fc:	e0ba                	sd	a4,64(sp)
    120005fe:	e4be                	sd	a5,72(sp)
    12000600:	e8c2                	sd	a6,80(sp)
    12000602:	ecc6                	sd	a7,88(sp)
    12000604:	e41a                	sd	t1,8(sp)
    12000606:	00000097          	auipc	ra,0x0
    1200060a:	f8c080e7          	jalr	-116(ra) # 12000592 <printf>
    1200060e:	65a2                	ld	a1,8(sp)
    12000610:	8522                	mv	a0,s0
    12000612:	00000097          	auipc	ra,0x0
    12000616:	cbc080e7          	jalr	-836(ra) # 120002ce <vprintf>
    1200061a:	00000097          	auipc	ra,0x0
    1200061e:	014080e7          	jalr	20(ra) # 1200062e <task_exit>

0000000012000622 <__panic_no_msg>:
    12000622:	1141                	addi	sp,sp,-16
    12000624:	e406                	sd	ra,8(sp)
    12000626:	00000097          	auipc	ra,0x0
    1200062a:	008080e7          	jalr	8(ra) # 1200062e <task_exit>

000000001200062e <task_exit>:
    1200062e:	4501                	li	a0,0
    12000630:	4581                	li	a1,0
    12000632:	4601                	li	a2,0
    12000634:	4681                	li	a3,0
    12000636:	4701                	li	a4,0
    12000638:	4885                	li	a7,1
    1200063a:	00000073          	ecall
    1200063e:	4881                	li	a7,0
    12000640:	00000073          	ecall

0000000012000644 <task_yield>:
    12000644:	4501                	li	a0,0
    12000646:	4581                	li	a1,0
    12000648:	4601                	li	a2,0
    1200064a:	4681                	li	a3,0
    1200064c:	4701                	li	a4,0
    1200064e:	48a1                	li	a7,8
    12000650:	00000073          	ecall
    12000654:	8082                	ret

0000000012000656 <task_gettid>:
    12000656:	00002517          	auipc	a0,0x2
    1200065a:	aba53503          	ld	a0,-1350(a0) # 12002110 <cached.0>
    1200065e:	ed01                	bnez	a0,12000676 <task_gettid+0x20>
    12000660:	4581                	li	a1,0
    12000662:	4601                	li	a2,0
    12000664:	4681                	li	a3,0
    12000666:	4701                	li	a4,0
    12000668:	4885                	li	a7,1
    1200066a:	00000073          	ecall
    1200066e:	00002797          	auipc	a5,0x2
    12000672:	aaa7b123          	sd	a0,-1374(a5) # 12002110 <cached.0>
    12000676:	8082                	ret

0000000012000678 <crt0>:
    12000678:	1141                	addi	sp,sp,-16
    1200067a:	4581                	li	a1,0
    1200067c:	4501                	li	a0,0
    1200067e:	e406                	sd	ra,8(sp)
    12000680:	00000097          	auipc	ra,0x0
    12000684:	010080e7          	jalr	16(ra) # 12000690 <__main>
    12000688:	00000097          	auipc	ra,0x0
    1200068c:	fa6080e7          	jalr	-90(ra) # 1200062e <task_exit>

0000000012000690 <__main>:
    12000690:	1141                	addi	sp,sp,-16
    12000692:	e406                	sd	ra,8(sp)
    12000694:	e022                	sd	s0,0(sp)
    12000696:	0800                	addi	s0,sp,16
    12000698:	00000097          	auipc	ra,0x0
    1200069c:	968080e7          	jalr	-1688(ra) # 12000000 <main>
    120006a0:	60a2                	ld	ra,8(sp)
    120006a2:	6402                	ld	s0,0(sp)
    120006a4:	0141                	addi	sp,sp,16
    120006a6:	8082                	ret

00000000120006a8 <memset>:
    120006a8:	ca01                	beqz	a2,120006b8 <memset+0x10>
    120006aa:	962a                	add	a2,a2,a0
    120006ac:	87aa                	mv	a5,a0
    120006ae:	0785                	addi	a5,a5,1
    120006b0:	feb78fa3          	sb	a1,-1(a5)
    120006b4:	fef61de3          	bne	a2,a5,120006ae <memset+0x6>
    120006b8:	8082                	ret

00000000120006ba <memcpy>:
    120006ba:	ca19                	beqz	a2,120006d0 <memcpy+0x16>
    120006bc:	962a                	add	a2,a2,a0
    120006be:	87aa                	mv	a5,a0
    120006c0:	0005c703          	lbu	a4,0(a1)
    120006c4:	0785                	addi	a5,a5,1
    120006c6:	0585                	addi	a1,a1,1
    120006c8:	fee78fa3          	sb	a4,-1(a5)
    120006cc:	fef61ae3          	bne	a2,a5,120006c0 <memcpy+0x6>
    120006d0:	8082                	ret

00000000120006d2 <memcmp>:
    120006d2:	c205                	beqz	a2,120006f2 <memcmp+0x20>
    120006d4:	962a                	add	a2,a2,a0
    120006d6:	a019                	j	120006dc <memcmp+0xa>
    120006d8:	00a60d63          	beq	a2,a0,120006f2 <memcmp+0x20>
    120006dc:	00054783          	lbu	a5,0(a0)
    120006e0:	0005c703          	lbu	a4,0(a1)
    120006e4:	0505                	addi	a0,a0,1
    120006e6:	0585                	addi	a1,a1,1
    120006e8:	fee788e3          	beq	a5,a4,120006d8 <memcmp+0x6>
    120006ec:	40e7853b          	subw	a0,a5,a4
    120006f0:	8082                	ret
    120006f2:	4501                	li	a0,0
    120006f4:	8082                	ret

00000000120006f6 <strlen>:
    120006f6:	00054783          	lbu	a5,0(a0)
    120006fa:	cb89                	beqz	a5,1200070c <strlen+0x16>
    120006fc:	87aa                	mv	a5,a0
    120006fe:	0017c703          	lbu	a4,1(a5)
    12000702:	0785                	addi	a5,a5,1
    12000704:	ff6d                	bnez	a4,120006fe <strlen+0x8>
    12000706:	40a78533          	sub	a0,a5,a0
    1200070a:	8082                	ret
    1200070c:	4501                	li	a0,0
    1200070e:	8082                	ret

0000000012000710 <strcpy>:
    12000710:	87aa                	mv	a5,a0
    12000712:	0005c703          	lbu	a4,0(a1)
    12000716:	0585                	addi	a1,a1,1
    12000718:	0785                	addi	a5,a5,1
    1200071a:	fee78fa3          	sb	a4,-1(a5)
    1200071e:	fb75                	bnez	a4,12000712 <strcpy+0x2>
    12000720:	8082                	ret

0000000012000722 <strncpy>:
    12000722:	4781                	li	a5,0
    12000724:	e619                	bnez	a2,12000732 <strncpy+0x10>
    12000726:	8082                	ret
    12000728:	00e68023          	sb	a4,0(a3)
    1200072c:	0785                	addi	a5,a5,1
    1200072e:	02f60263          	beq	a2,a5,12000752 <strncpy+0x30>
    12000732:	00f58733          	add	a4,a1,a5
    12000736:	00074703          	lbu	a4,0(a4)
    1200073a:	00f506b3          	add	a3,a0,a5
    1200073e:	f76d                	bnez	a4,12000728 <strncpy+0x6>
    12000740:	00c7f963          	bgeu	a5,a2,12000752 <strncpy+0x30>
    12000744:	87b6                	mv	a5,a3
    12000746:	962a                	add	a2,a2,a0
    12000748:	00078023          	sb	zero,0(a5)
    1200074c:	0785                	addi	a5,a5,1
    1200074e:	fef61de3          	bne	a2,a5,12000748 <strncpy+0x26>
    12000752:	8082                	ret

0000000012000754 <strcat>:
    12000754:	00054783          	lbu	a5,0(a0)
    12000758:	cf91                	beqz	a5,12000774 <strcat+0x20>
    1200075a:	87aa                	mv	a5,a0
    1200075c:	0017c703          	lbu	a4,1(a5)
    12000760:	0785                	addi	a5,a5,1
    12000762:	ff6d                	bnez	a4,1200075c <strcat+0x8>
    12000764:	0005c703          	lbu	a4,0(a1)
    12000768:	0585                	addi	a1,a1,1
    1200076a:	0785                	addi	a5,a5,1
    1200076c:	fee78fa3          	sb	a4,-1(a5)
    12000770:	fb75                	bnez	a4,12000764 <strcat+0x10>
    12000772:	8082                	ret
    12000774:	0005c703          	lbu	a4,0(a1)
    12000778:	87aa                	mv	a5,a0
    1200077a:	0585                	addi	a1,a1,1
    1200077c:	00e78023          	sb	a4,0(a5)
    12000780:	0785                	addi	a5,a5,1
    12000782:	f36d                	bnez	a4,12000764 <strcat+0x10>
    12000784:	8082                	ret

0000000012000786 <strcmp>:
    12000786:	00054783          	lbu	a5,0(a0)
    1200078a:	e791                	bnez	a5,12000796 <strcmp+0x10>
    1200078c:	a01d                	j	120007b2 <strcmp+0x2c>
    1200078e:	00054783          	lbu	a5,0(a0)
    12000792:	cb99                	beqz	a5,120007a8 <strcmp+0x22>
    12000794:	0585                	addi	a1,a1,1
    12000796:	0005c703          	lbu	a4,0(a1)
    1200079a:	0505                	addi	a0,a0,1
    1200079c:	fef709e3          	beq	a4,a5,1200078e <strcmp+0x8>
    120007a0:	0007851b          	sext.w	a0,a5
    120007a4:	9d19                	subw	a0,a0,a4
    120007a6:	8082                	ret
    120007a8:	0015c703          	lbu	a4,1(a1)
    120007ac:	4501                	li	a0,0
    120007ae:	9d19                	subw	a0,a0,a4
    120007b0:	8082                	ret
    120007b2:	0005c703          	lbu	a4,0(a1)
    120007b6:	4501                	li	a0,0
    120007b8:	b7f5                	j	120007a4 <strcmp+0x1e>

Disassembly of section .rodata:

0000000012001000 <__srodata>:
    12001000:	6568                	ld	a0,200(a0)
    12001002:	6c6c                	ld	a1,216(s0)
    12001004:	7266206f          	j	1206372a <__sheap+0x6072a>
    12001008:	68206d6f          	jal	s10,1200768a <__sheap+0x468a>
    1200100c:	6c65                	lui	s8,0x19
    1200100e:	6f6c                	ld	a1,216(a4)
    12001010:	6120                	ld	s0,64(a0)
    12001012:	7070                	ld	a2,224(s0)
    12001014:	0a21                	addi	s4,s4,8
	...
    1200101e:	0000                	unimp
    12001020:	6568                	ld	a0,200(a0)
    12001022:	6c6c                	ld	a1,216(s0)
    12001024:	6f63206f          	j	1203371a <__sheap+0x3071a>
    12001028:	6e75                	lui	t3,0x1d
    1200102a:	6574                	ld	a3,200(a0)
    1200102c:	3a72                	fld	fs4,312(sp)
    1200102e:	2520                	fld	fs0,72(a0)
    12001030:	646c                	ld	a1,200(s0)
    12001032:	000a                	c.slli	zero,0x2
    12001034:	0000                	unimp
    12001036:	0000                	unimp
    12001038:	3130                	fld	fa2,96(a0)
    1200103a:	3332                	fld	ft6,296(sp)
    1200103c:	3534                	fld	fa3,104(a0)
    1200103e:	3736                	fld	fa4,360(sp)
    12001040:	3938                	fld	fa4,112(a0)
    12001042:	6261                	lui	tp,0x18
    12001044:	66656463          	bltu	a0,t1,120016ac <__erodata+0x598>
	...
    12001050:	6e28                	ld	a0,88(a2)
    12001052:	6c75                	lui	s8,0x1d
    12001054:	296c                	fld	fa1,208(a0)
    12001056:	0000                	unimp
    12001058:	7076                	.insn	2, 0x7076
    1200105a:	6972                	ld	s2,280(sp)
    1200105c:	746e                	ld	s0,248(sp)
    1200105e:	3a66                	fld	fs4,120(sp)
    12001060:	7520                	ld	s0,104(a0)
    12001062:	736e                	ld	t1,248(sp)
    12001064:	7075                	c.lui	zero,0xffffd
    12001066:	6f70                	ld	a2,216(a4)
    12001068:	7472                	ld	s0,312(sp)
    1200106a:	6465                	lui	s0,0x19
    1200106c:	6620                	ld	s0,72(a2)
    1200106e:	616d726f          	jal	tp,120d8684 <__sheap+0xd5684>
    12001072:	2074                	fld	fa3,192(s0)
    12001074:	63657073          	csrci	0x636,10
    12001078:	6669                	lui	a2,0x1a
    1200107a:	6569                	lui	a0,0x1a
    1200107c:	2072                	fld	ft0,280(sp)
    1200107e:	6661                	lui	a2,0x18
    12001080:	6574                	ld	a3,200(a0)
    12001082:	2072                	fld	ft0,280(sp)
    12001084:	00276c27          	.insn	4, 0x00276c27
    12001088:	7076                	.insn	2, 0x7076
    1200108a:	6972                	ld	s2,280(sp)
    1200108c:	746e                	ld	s0,248(sp)
    1200108e:	75203a6b          	.insn	4, 0x75203a6b
    12001092:	736e                	ld	t1,248(sp)
    12001094:	7075                	c.lui	zero,0xffffd
    12001096:	6f70                	ld	a2,216(a4)
    12001098:	7472                	ld	s0,312(sp)
    1200109a:	6465                	lui	s0,0x19
    1200109c:	6620                	ld	s0,72(a2)
    1200109e:	616d726f          	jal	tp,120d86b4 <__sheap+0xd56b4>
    120010a2:	2074                	fld	fa3,192(s0)
    120010a4:	63657073          	csrci	0x636,10
    120010a8:	6669                	lui	a2,0x1a
    120010aa:	6569                	lui	a0,0x1a
    120010ac:	0072                	c.slli	zero,0x1c
    120010ae:	0000                	unimp
    120010b0:	4150                	lw	a2,4(a0)
    120010b2:	494e                	lw	s2,208(sp)
    120010b4:	00203a43          	fmadd.s	fs4,ft0,ft2,ft0,rup
    120010b8:	f3d2                	sd	s4,480(sp)
    120010ba:	ffff                	.insn	2, 0xffff
    120010bc:	f3be                	sd	a5,480(sp)
    120010be:	ffff                	.insn	2, 0xffff
    120010c0:	f3a4                	sd	s1,96(a5)
    120010c2:	ffff                	.insn	2, 0xffff
    120010c4:	f2b4                	sd	a3,96(a3)
    120010c6:	ffff                	.insn	2, 0xffff
    120010c8:	f2b4                	sd	a3,96(a3)
    120010ca:	ffff                	.insn	2, 0xffff
    120010cc:	f2b4                	sd	a3,96(a3)
    120010ce:	ffff                	.insn	2, 0xffff
    120010d0:	f2b4                	sd	a3,96(a3)
    120010d2:	ffff                	.insn	2, 0xffff
    120010d4:	f2b4                	sd	a3,96(a3)
    120010d6:	ffff                	.insn	2, 0xffff
    120010d8:	f2b4                	sd	a3,96(a3)
    120010da:	ffff                	.insn	2, 0xffff
    120010dc:	f2b4                	sd	a3,96(a3)
    120010de:	ffff                	.insn	2, 0xffff
    120010e0:	f368                	sd	a0,224(a4)
    120010e2:	ffff                	.insn	2, 0xffff
    120010e4:	f2b4                	sd	a3,96(a3)
    120010e6:	ffff                	.insn	2, 0xffff
    120010e8:	f2b4                	sd	a3,96(a3)
    120010ea:	ffff                	.insn	2, 0xffff
    120010ec:	f34e                	sd	s3,416(sp)
    120010ee:	ffff                	.insn	2, 0xffff
    120010f0:	f318                	sd	a4,32(a4)
    120010f2:	ffff                	.insn	2, 0xffff
    120010f4:	f2b4                	sd	a3,96(a3)
    120010f6:	ffff                	.insn	2, 0xffff
    120010f8:	f2b4                	sd	a3,96(a3)
    120010fa:	ffff                	.insn	2, 0xffff
    120010fc:	f2e2                	sd	s8,352(sp)
    120010fe:	ffff                	.insn	2, 0xffff
    12001100:	f2b4                	sd	a3,96(a3)
    12001102:	ffff                	.insn	2, 0xffff
    12001104:	f2b4                	sd	a3,96(a3)
    12001106:	ffff                	.insn	2, 0xffff
    12001108:	f2b4                	sd	a3,96(a3)
    1200110a:	ffff                	.insn	2, 0xffff
    1200110c:	f2b4                	sd	a3,96(a3)
    1200110e:	ffff                	.insn	2, 0xffff
    12001110:	f2c8                	sd	a0,160(a3)
    12001112:	ffff                	.insn	2, 0xffff

Disassembly of section .debug_info:

0000000000000000 <.debug_info>:
       0:	0000016f          	jal	sp,0 <main-0x12000000>
       4:	0005                	c.nop	1
       6:	0801                	addi	a6,a6,0
       8:	0000                	unimp
       a:	0000                	unimp
       c:	00002b07          	flw	fs6,0(zero) # 0 <main-0x12000000>
      10:	1d00                	addi	s0,sp,688
      12:	0046                	c.slli	zero,0x11
      14:	0000                	unimp
      16:	004d                	c.nop	19
      18:	0000                	unimp
      1a:	000c                	.insn	2, 0x000c
	...
      28:	0000                	unimp
      2a:	0101                	addi	sp,sp,0
      2c:	0b08                	addi	a0,sp,400
      2e:	0001                	nop
      30:	0100                	addi	s0,sp,128
      32:	0601                	addi	a2,a2,0 # 1a000 <main-0x11fe6000>
      34:	010d                	addi	sp,sp,3
      36:	0000                	unimp
      38:	0201                	addi	tp,tp,0 # 18000 <main-0x11fe8000>
      3a:	00012d07          	flw	fs10,0(sp)
      3e:	0100                	addi	s0,sp,128
      40:	0502                	c.slli64	a0
      42:	0000014b          	fnmsub.s	ft2,ft0,ft0,ft0,rne
      46:	0401                	addi	s0,s0,0 # 19000 <main-0x11fe7000>
      48:	00001e07          	.insn	4, 0x1e07
      4c:	0800                	addi	s0,sp,16
      4e:	0504                	addi	s1,sp,640
      50:	6e69                	lui	t3,0x1a
      52:	0074                	addi	a3,sp,12
      54:	34367503          	.insn	4, 0x34367503
      58:	3d00                	fld	fs0,56(a0)
      5a:	005e                	c.slli	zero,0x17
      5c:	0000                	unimp
      5e:	0801                	addi	a6,a6,0
      60:	00001407          	.insn	4, 0x1407
      64:	0300                	addi	s0,sp,384
      66:	3669                	addiw	a2,a2,-6
      68:	0034                	addi	a3,sp,8
      6a:	6f3e                	ld	t5,456(sp)
      6c:	0000                	unimp
      6e:	0100                	addi	s0,sp,128
      70:	0508                	addi	a0,sp,640
      72:	0000                	unimp
      74:	0000                	unimp
      76:	0401                	addi	s0,s0,0
      78:	4504                	lw	s1,8(a0)
      7a:	0001                	nop
      7c:	0100                	addi	s0,sp,128
      7e:	0408                	addi	a0,sp,512
      80:	0119                	addi	sp,sp,6
      82:	0000                	unimp
      84:	0e09                	addi	t3,t3,2 # 1a002 <main-0x11fe5ffe>
      86:	0000                	unimp
      88:	0200                	addi	s0,sp,256
      8a:	00650d43          	fmadd.s	fs10,fa0,ft6,ft0,rne
      8e:	0000                	unimp
      90:	250a                	fld	fa0,128(sp)
      92:	0001                	nop
      94:	0100                	addi	s0,sp,128
      96:	00540507          	.insn	4, 0x00540507
      9a:	0000                	unimp
      9c:	0309                	addi	t1,t1,2
      9e:	2100                	fld	fs0,0(a0)
      a0:	1200                	addi	s0,sp,288
      a2:	0000                	unimp
      a4:	0000                	unimp
      a6:	0002660b          	.insn	4, 0x0002660b
      aa:	0300                	addi	s0,sp,384
      ac:	900c0907          	.insn	4, 0x900c0907
      b0:	0001                	nop
      b2:	0400                	addi	s0,sp,512
      b4:	0914                	addi	a3,sp,144
      b6:	0084                	addi	s1,sp,64
      b8:	0000                	unimp
      ba:	00c5                	addi	ra,ra,17
      bc:	0000                	unimp
      be:	c50d                	beqz	a0,e8 <main-0x11ffff18>
      c0:	0000                	unimp
      c2:	0e00                	addi	s0,sp,784
      c4:	0200                	addi	s0,sp,256
      c6:	00d1                	addi	ra,ra,20
      c8:	0000                	unimp
      ca:	0101                	addi	sp,sp,0
      cc:	1408                	addi	a0,sp,544
      ce:	0001                	nop
      d0:	0f00                	addi	s0,sp,912
      d2:	00ca                	slli	ra,ra,0x12
      d4:	0000                	unimp
      d6:	9810                	.insn	2, 0x9810
      d8:	0002                	c.slli64	zero
      da:	0100                	addi	s0,sp,128
      dc:	010a                	slli	sp,sp,0x2
      de:	0084                	addi	s1,sp,64
      e0:	0000                	unimp
      e2:	0000                	unimp
      e4:	1200                	addi	s0,sp,288
      e6:	0000                	unimp
      e8:	0000                	unimp
      ea:	0040                	addi	s0,sp,4
      ec:	0000                	unimp
      ee:	0000                	unimp
      f0:	0000                	unimp
      f2:	9c01                	subw	s0,s0,s0
      f4:	0168                	addi	a0,sp,140
      f6:	0000                	unimp
      f8:	2004                	fld	fs1,0(s0)
      fa:	0001                	nop
      fc:	0a00                	addi	s0,sp,272
      fe:	004d                	c.nop	19
     100:	0000                	unimp
     102:	0010                	.insn	2, 0x0010
     104:	0000                	unimp
     106:	000c                	.insn	2, 0x000c
     108:	0000                	unimp
     10a:	4004                	lw	s1,0(s0)
     10c:	0001                	nop
     10e:	1600                	addi	s0,sp,800
     110:	0168                	addi	a0,sp,140
     112:	0000                	unimp
     114:	0000002b          	.insn	4, 0x002b
     118:	00000027          	.insn	4, 0x0027
     11c:	1e05                	addi	t3,t3,-31
     11e:	0000                	unimp
     120:	0012                	c.slli	zero,0x4
     122:	0000                	unimp
     124:	ae00                	fsd	fs0,24(a2)
     126:	0000                	unimp
     128:	3b00                	fld	fs0,48(a4)
     12a:	0001                	nop
     12c:	0600                	addi	s0,sp,768
     12e:	5a01                	li	s4,-32
     130:	0309                	addi	t1,t1,2
     132:	1000                	addi	s0,sp,32
     134:	1200                	addi	s0,sp,288
     136:	0000                	unimp
     138:	0000                	unimp
     13a:	0500                	addi	s0,sp,640
     13c:	0036                	c.slli	zero,0xd
     13e:	1200                	addi	s0,sp,288
     140:	0000                	unimp
     142:	0000                	unimp
     144:	00ae                	slli	ra,ra,0xb
     146:	0000                	unimp
     148:	015a                	slli	sp,sp,0x16
     14a:	0000                	unimp
     14c:	0106                	slli	sp,sp,0x1
     14e:	095a                	slli	s2,s2,0x16
     150:	00102003          	lw	zero,1(zero) # 1 <main-0x11ffffff>
     154:	0012                	c.slli	zero,0x4
     156:	0000                	unimp
     158:	0000                	unimp
     15a:	3e11                	addiw	t3,t3,-28
     15c:	0000                	unimp
     15e:	0012                	c.slli	zero,0x4
     160:	0000                	unimp
     162:	a600                	fsd	fs0,8(a2)
     164:	0000                	unimp
     166:	0000                	unimp
     168:	6d02                	ld	s10,0(sp)
     16a:	0001                	nop
     16c:	0200                	addi	s0,sp,256
     16e:	00ca                	slli	ra,ra,0x12
     170:	0000                	unimp
     172:	3d00                	fld	fs0,56(a0)
     174:	0009                	c.nop	2
     176:	0500                	addi	s0,sp,640
     178:	0100                	addi	s0,sp,128
     17a:	f408                	sd	a0,40(s0)
     17c:	0000                	unimp
     17e:	1e00                	addi	s0,sp,816
     180:	0000002b          	.insn	4, 0x002b
     184:	a61d                	j	4aa <main-0x11fffb56>
     186:	0000                	unimp
     188:	3c00                	fld	fs0,56(s0)
     18a:	0001                	nop
     18c:	4000                	lw	s0,0(s0)
     18e:	0000                	unimp
     190:	0012                	c.slli	zero,0x4
     192:	0000                	unimp
     194:	7a00                	ld	s0,48(a2)
     196:	0005                	c.nop	1
     198:	0000                	unimp
     19a:	0000                	unimp
     19c:	a900                	fsd	fs0,16(a0)
     19e:	0000                	unimp
     1a0:	0300                	addi	s0,sp,384
     1a2:	0708                	addi	a0,sp,896
     1a4:	0019                	c.nop	6
     1a6:	0000                	unimp
     1a8:	9f0d                	subw	a4,a4,a1
     1aa:	0001                	nop
     1ac:	0200                	addi	s0,sp,256
     1ae:	1b28                	addi	a0,sp,440
     1b0:	0041                	c.nop	16
     1b2:	0000                	unimp
     1b4:	081f 015c 0000      	.insn	6, 0x015c081f
     1ba:	a60d                	j	4dc <main-0x11fffb24>
     1bc:	0001                	nop
     1be:	0200                	addi	s0,sp,256
     1c0:	00351867          	.insn	4, 0x00351867
     1c4:	0000                	unimp
     1c6:	7511                	lui	a0,0xfffe4
     1c8:	0038                	addi	a4,sp,8
     1ca:	00005c37          	lui	s8,0x5
     1ce:	0300                	addi	s0,sp,384
     1d0:	0801                	addi	a6,a6,0
     1d2:	0000010b          	.insn	4, 0x010b
     1d6:	0d060103          	lb	sp,208(a2)
     1da:	0001                	nop
     1dc:	0300                	addi	s0,sp,384
     1de:	0702                	c.slli64	a4
     1e0:	012d                	addi	sp,sp,11
     1e2:	0000                	unimp
     1e4:	4b050203          	lb	tp,1200(a0) # fffffffffffe44b0 <__sheap+0xffffffffedfe14b0>
     1e8:	0001                	nop
     1ea:	0300                	addi	s0,sp,384
     1ec:	0704                	addi	s1,sp,896
     1ee:	001e                	c.slli	zero,0x7
     1f0:	0000                	unimp
     1f2:	0420                	addi	s0,sp,520
     1f4:	6905                	lui	s2,0x1
     1f6:	746e                	ld	s0,248(sp)
     1f8:	1100                	addi	s0,sp,160
     1fa:	3675                	addiw	a2,a2,-3
     1fc:	0034                	addi	a3,sp,8
     1fe:	903d                	srli	s0,s0,0x2f
     200:	0000                	unimp
     202:	0300                	addi	s0,sp,384
     204:	0708                	addi	a0,sp,896
     206:	0014                	.insn	2, 0x0014
     208:	0000                	unimp
     20a:	6911                	lui	s2,0x4
     20c:	3436                	fld	fs0,360(sp)
     20e:	3e00                	fld	fs0,56(a2)
     210:	00a1                	addi	ra,ra,8
     212:	0000                	unimp
     214:	00050803          	lb	a6,0(a0)
     218:	0000                	unimp
     21a:	0300                	addi	s0,sp,384
     21c:	0404                	addi	s1,sp,512
     21e:	0145                	addi	sp,sp,17
     220:	0000                	unimp
     222:	19040803          	lb	a6,400(s0)
     226:	0001                	nop
     228:	0d00                	addi	s0,sp,656
     22a:	01e9                	addi	gp,gp,26
     22c:	0000                	unimp
     22e:	860d4203          	lbu	tp,-1952(s10)
     232:	0000                	unimp
     234:	0d00                	addi	s0,sp,656
     236:	000e                	c.slli	zero,0x3
     238:	0000                	unimp
     23a:	970d4303          	lbu	t1,-1680(s10)
     23e:	0000                	unimp
     240:	1200                	addi	s0,sp,288
     242:	00de                	slli	ra,ra,0x17
     244:	0000                	unimp
     246:	00de                	slli	ra,ra,0x17
     248:	0000                	unimp
     24a:	00002e13          	slti	t3,zero,0
     24e:	ff00                	sd	s0,56(a4)
     250:	0300                	addi	s0,sp,384
     252:	0801                	addi	a6,a6,0
     254:	0114                	addi	a3,sp,128
     256:	0000                	unimp
     258:	de21                	beqz	a2,1b0 <main-0x11fffe50>
     25a:	0000                	unimp
     25c:	0a00                	addi	s0,sp,272
     25e:	7562                	ld	a0,56(sp)
     260:	0066                	c.slli	zero,0x19
     262:	0d08                	addi	a0,sp,656
     264:	00ce                	slli	ra,ra,0x13
     266:	0000                	unimp
     268:	0309                	addi	t1,t1,2
     26a:	2000                	fld	fs0,0(s0)
     26c:	1200                	addi	s0,sp,288
     26e:	0000                	unimp
     270:	0000                	unimp
     272:	b814                	fsd	fa3,48(s0)
     274:	0001                	nop
     276:	0900                	addi	s0,sp,144
     278:	b60e                	fsd	ft3,296(sp)
     27a:	0000                	unimp
     27c:	0900                	addi	s0,sp,144
     27e:	00210803          	lb	a6,2(sp)
     282:	0012                	c.slli	zero,0x4
     284:	0000                	unimp
     286:	2200                	fld	fs0,0(a2)
     288:	01da                	slli	gp,gp,0x16
     28a:	0000                	unimp
     28c:	1104                	addi	s1,sp,160
     28e:	b610                	fsd	fa2,40(a2)
     290:	0000                	unimp
     292:	2a00                	fld	fs0,16(a2)
     294:	0001                	nop
     296:	1500                	addi	s0,sp,672
     298:	012a                	slli	sp,sp,0xa
     29a:	0000                	unimp
     29c:	2300                	fld	fs0,0(a4)
     29e:	e508                	sd	a0,8(a0)
     2a0:	0000                	unimp
     2a2:	2400                	fld	fs0,8(s0)
     2a4:	01e1                	addi	gp,gp,24
     2a6:	0000                	unimp
     2a8:	0d05                	addi	s10,s10,1
     2aa:	430d                	li	t1,3
     2ac:	0001                	nop
     2ae:	1500                	addi	s0,sp,672
     2b0:	012a                	slli	sp,sp,0xa
     2b2:	0000                	unimp
     2b4:	0016                	c.slli	zero,0x5
     2b6:	00019017          	auipc	zero,0x19
     2ba:	b800                	fsd	fs0,48(s0)
     2bc:	00c2                	slli	ra,ra,0x10
     2be:	0000                	unimp
     2c0:	0592                	slli	a1,a1,0x4
     2c2:	1200                	addi	s0,sp,288
     2c4:	0000                	unimp
     2c6:	0000                	unimp
     2c8:	0028                	addi	a0,sp,8
     2ca:	0000                	unimp
     2cc:	0000                	unimp
     2ce:	0000                	unimp
     2d0:	9c01                	subw	s0,s0,s0
     2d2:	01b4                	addi	a3,sp,200
     2d4:	0000                	unimp
     2d6:	746d660b          	.insn	4, 0x746d660b
     2da:	b800                	fsd	fs0,48(s0)
     2dc:	2a14                	fld	fa3,16(a2)
     2de:	0001                	nop
     2e0:	5200                	lw	s0,32(a2)
     2e2:	0000                	unimp
     2e4:	4e00                	lw	s0,24(a2)
     2e6:	0000                	unimp
     2e8:	1600                	addi	s0,sp,800
     2ea:	610a                	ld	sp,128(sp)
     2ec:	0070                	addi	a2,sp,12
     2ee:	0db9                	addi	s11,s11,14
     2f0:	00000047          	fmsub.s	ft0,ft0,ft0,ft0,rne
     2f4:	7fa89103          	lh	sp,2042(a7)
     2f8:	7206                	ld	tp,96(sp)
     2fa:	7465                	lui	s0,0xffff9
     2fc:	bb00                	fsd	fs0,48(a4)
     2fe:	0000c20b          	.insn	4, 0xc20b
     302:	6600                	ld	s0,8(a2)
     304:	0000                	unimp
     306:	6400                	ld	s0,8(s0)
     308:	0000                	unimp
     30a:	0200                	addi	s0,sp,256
     30c:	05b4                	addi	a3,sp,712
     30e:	1200                	addi	s0,sp,288
     310:	0000                	unimp
     312:	0000                	unimp
     314:	01b4                	addi	a3,sp,200
     316:	0000                	unimp
     318:	0101                	addi	sp,sp,0
     31a:	035a                	slli	t1,t1,0x16
     31c:	015a01a3          	sb	s5,3(s4)
     320:	5b01                	li	s6,-32
     322:	9102                	jalr	sp
     324:	0048                	addi	a0,sp,4
     326:	1700                	addi	s0,sp,928
     328:	0000018f          	.insn	4, 0x018f
     32c:	c266                	sw	s9,4(sp)
     32e:	0000                	unimp
     330:	ce00                	sw	s0,24(a2)
     332:	0002                	c.slli64	zero
     334:	0012                	c.slli	zero,0x4
     336:	0000                	unimp
     338:	c400                	sw	s0,8(s0)
     33a:	0002                	c.slli64	zero
     33c:	0000                	unimp
     33e:	0000                	unimp
     340:	0100                	addi	s0,sp,128
     342:	e89c                	sd	a5,16(s1)
     344:	0005                	c.nop	1
     346:	0b00                	addi	s0,sp,400
     348:	6d66                	ld	s10,88(sp)
     34a:	0074                	addi	a3,sp,12
     34c:	1566                	slli	a0,a0,0x39
     34e:	012a                	slli	sp,sp,0xa
     350:	0000                	unimp
     352:	007e                	c.slli	zero,0x1f
     354:	0000                	unimp
     356:	006e                	c.slli	zero,0x1b
     358:	0000                	unimp
     35a:	0070610b          	.insn	4, 0x0070610b
     35e:	2266                	fld	ft4,88(sp)
     360:	00000047          	fmsub.s	ft0,ft0,ft0,ft0,rne
     364:	00fd                	addi	ra,ra,31
     366:	0000                	unimp
     368:	000000af          	.insn	4, 0x00af
     36c:	970c                	.insn	2, 0x970c
     36e:	0001                	nop
     370:	6a00                	ld	s0,16(a2)
     372:	0000c20b          	.insn	4, 0xc20b
     376:	ec00                	sd	s0,24(s0)
     378:	0001                	nop
     37a:	c800                	sw	s0,16(s0)
     37c:	0001                	nop
     37e:	0400                	addi	s0,sp,512
     380:	000000af          	.insn	4, 0x00af
     384:	05aa                	slli	a1,a1,0xa
     386:	0000                	unimp
     388:	6906                	ld	s2,64(sp)
     38a:	6b00                	ld	s0,16(a4)
     38c:	b610                	fsd	fa2,40(a2)
     38e:	0000                	unimp
     390:	6700                	ld	s0,8(a4)
     392:	0002                	c.slli64	zero
     394:	4900                	lw	s0,16(a0)
     396:	0002                	c.slli64	zero
     398:	0e00                	addi	s0,sp,784
     39a:	0520                	addi	s0,sp,648
     39c:	1200                	addi	s0,sp,288
     39e:	0000                	unimp
     3a0:	0000                	unimp
     3a2:	0016                	c.slli	zero,0x5
     3a4:	0000                	unimp
     3a6:	0000                	unimp
     3a8:	0000                	unimp
     3aa:	0264                	addi	s1,sp,268
     3ac:	0000                	unimp
     3ae:	6e05                	lui	t3,0x1
     3b0:	6d75                	lui	s10,0x1d
     3b2:	7200                	ld	s0,32(a2)
     3b4:	971d                	srai	a4,a4,0x27
     3b6:	0000                	unimp
     3b8:	0200                	addi	s0,sp,256
     3ba:	0532                	slli	a0,a0,0xc
     3bc:	1200                	addi	s0,sp,288
     3be:	0000                	unimp
     3c0:	0000                	unimp
     3c2:	05ea                	slli	a1,a1,0x1a
     3c4:	0000                	unimp
     3c6:	0101                	addi	sp,sp,0
     3c8:	013a015b          	.insn	4, 0x013a015b
     3cc:	5c01                	li	s8,-32
     3ce:	3101                	addiw	sp,sp,-32
     3d0:	0101                	addi	sp,sp,0
     3d2:	015d                	addi	sp,sp,23
     3d4:	0030                	addi	a2,sp,8
     3d6:	0e00                	addi	s0,sp,784
     3d8:	0538                	addi	a4,sp,648
     3da:	1200                	addi	s0,sp,288
     3dc:	0000                	unimp
     3de:	0000                	unimp
     3e0:	0016                	c.slli	zero,0x5
     3e2:	0000                	unimp
     3e4:	0000                	unimp
     3e6:	0000                	unimp
     3e8:	02a2                	slli	t0,t0,0x8
     3ea:	0000                	unimp
     3ec:	6e05                	lui	t3,0x1
     3ee:	6d75                	lui	s10,0x1d
     3f0:	7500                	ld	s0,40(a0)
     3f2:	861d                	srai	a2,a2,0x7
     3f4:	0000                	unimp
     3f6:	0200                	addi	s0,sp,256
     3f8:	054a                	slli	a0,a0,0x12
     3fa:	1200                	addi	s0,sp,288
     3fc:	0000                	unimp
     3fe:	0000                	unimp
     400:	05ea                	slli	a1,a1,0x1a
     402:	0000                	unimp
     404:	0101                	addi	sp,sp,0
     406:	0140015b          	.insn	4, 0x0140015b
     40a:	5c01                	li	s8,-32
     40c:	3001                	.insn	2, 0x3001
     40e:	0101                	addi	sp,sp,0
     410:	015d                	addi	sp,sp,23
     412:	0030                	addi	a2,sp,8
     414:	0e00                	addi	s0,sp,784
     416:	0550                	addi	a2,sp,644
     418:	1200                	addi	s0,sp,288
     41a:	0000                	unimp
     41c:	0000                	unimp
     41e:	0016                	c.slli	zero,0x5
     420:	0000                	unimp
     422:	0000                	unimp
     424:	0000                	unimp
     426:	02e0                	addi	s0,sp,332
     428:	0000                	unimp
     42a:	6e05                	lui	t3,0x1
     42c:	6d75                	lui	s10,0x1d
     42e:	7800                	ld	s0,48(s0)
     430:	861d                	srai	a2,a2,0x7
     432:	0000                	unimp
     434:	0200                	addi	s0,sp,256
     436:	0562                	slli	a0,a0,0x18
     438:	1200                	addi	s0,sp,288
     43a:	0000                	unimp
     43c:	0000                	unimp
     43e:	05ea                	slli	a1,a1,0x1a
     440:	0000                	unimp
     442:	0101                	addi	sp,sp,0
     444:	0132015b          	.insn	4, 0x0132015b
     448:	5c01                	li	s8,-32
     44a:	3001                	.insn	2, 0x3001
     44c:	0101                	addi	sp,sp,0
     44e:	015d                	addi	sp,sp,23
     450:	0030                	addi	a2,sp,8
     452:	0e00                	addi	s0,sp,784
     454:	04fc                	addi	a5,sp,588
     456:	1200                	addi	s0,sp,288
     458:	0000                	unimp
     45a:	0000                	unimp
     45c:	0016                	c.slli	zero,0x5
     45e:	0000                	unimp
     460:	0000                	unimp
     462:	0000                	unimp
     464:	031e                	slli	t1,t1,0x7
     466:	0000                	unimp
     468:	6e05                	lui	t3,0x1
     46a:	6d75                	lui	s10,0x1d
     46c:	7b00                	ld	s0,48(a4)
     46e:	861d                	srai	a2,a2,0x7
     470:	0000                	unimp
     472:	0200                	addi	s0,sp,256
     474:	050e                	slli	a0,a0,0x3
     476:	1200                	addi	s0,sp,288
     478:	0000                	unimp
     47a:	0000                	unimp
     47c:	05ea                	slli	a1,a1,0x1a
     47e:	0000                	unimp
     480:	0101                	addi	sp,sp,0
     482:	0138015b          	.insn	4, 0x0138015b
     486:	5c01                	li	s8,-32
     488:	3001                	.insn	2, 0x3001
     48a:	0101                	addi	sp,sp,0
     48c:	015d                	addi	sp,sp,23
     48e:	0030                	addi	a2,sp,8
     490:	0400                	addi	s0,sp,512
     492:	0115                	addi	sp,sp,5
     494:	0000                	unimp
     496:	0358                	addi	a4,sp,388
     498:	0000                	unimp
     49a:	6e06                	ld	t3,64(sp)
     49c:	6d75                	lui	s10,0x1d
     49e:	8300                	.insn	2, 0x8300
     4a0:	9719                	srai	a4,a4,0x26
     4a2:	0000                	unimp
     4a4:	bb00                	fsd	fs0,48(a4)
     4a6:	0002                	c.slli64	zero
     4a8:	b700                	fsd	fs0,40(a4)
     4aa:	0002                	c.slli64	zero
     4ac:	0200                	addi	s0,sp,256
     4ae:	046e                	slli	s0,s0,0x1b
     4b0:	1200                	addi	s0,sp,288
     4b2:	0000                	unimp
     4b4:	0000                	unimp
     4b6:	05ea                	slli	a1,a1,0x1a
     4b8:	0000                	unimp
     4ba:	0101                	addi	sp,sp,0
     4bc:	013a015b          	.insn	4, 0x013a015b
     4c0:	5c01                	li	s8,-32
     4c2:	3101                	addiw	sp,sp,-32
     4c4:	0101                	addi	sp,sp,0
     4c6:	015d                	addi	sp,sp,23
     4c8:	0030                	addi	a2,sp,8
     4ca:	0400                	addi	s0,sp,512
     4cc:	00ce                	slli	ra,ra,0x13
     4ce:	0000                	unimp
     4d0:	038a                	slli	t2,t2,0x2
     4d2:	0000                	unimp
     4d4:	6e05                	lui	t3,0x1
     4d6:	6d75                	lui	s10,0x1d
     4d8:	8800                	.insn	2, 0x8800
     4da:	8619                	srai	a2,a2,0x6
     4dc:	0000                	unimp
     4de:	0200                	addi	s0,sp,256
     4e0:	0392                	slli	t2,t2,0x4
     4e2:	1200                	addi	s0,sp,288
     4e4:	0000                	unimp
     4e6:	0000                	unimp
     4e8:	05ea                	slli	a1,a1,0x1a
     4ea:	0000                	unimp
     4ec:	0101                	addi	sp,sp,0
     4ee:	0140015b          	.insn	4, 0x0140015b
     4f2:	5c01                	li	s8,-32
     4f4:	3001                	.insn	2, 0x3001
     4f6:	0101                	addi	sp,sp,0
     4f8:	015d                	addi	sp,sp,23
     4fa:	0030                	addi	a2,sp,8
     4fc:	0400                	addi	s0,sp,512
     4fe:	0000012b          	.insn	4, 0x012b
     502:	03bc                	addi	a5,sp,456
     504:	0000                	unimp
     506:	6e05                	lui	t3,0x1
     508:	6d75                	lui	s10,0x1d
     50a:	8d00                	.insn	2, 0x8d00
     50c:	8619                	srai	a2,a2,0x6
     50e:	0000                	unimp
     510:	0200                	addi	s0,sp,256
     512:	049c                	addi	a5,sp,576
     514:	1200                	addi	s0,sp,288
     516:	0000                	unimp
     518:	0000                	unimp
     51a:	05ea                	slli	a1,a1,0x1a
     51c:	0000                	unimp
     51e:	0101                	addi	sp,sp,0
     520:	0132015b          	.insn	4, 0x0132015b
     524:	5c01                	li	s8,-32
     526:	3001                	.insn	2, 0x3001
     528:	0101                	addi	sp,sp,0
     52a:	015d                	addi	sp,sp,23
     52c:	0030                	addi	a2,sp,8
     52e:	0400                	addi	s0,sp,512
     530:	010a                	slli	sp,sp,0x2
     532:	0000                	unimp
     534:	03ee                	slli	t2,t2,0x1b
     536:	0000                	unimp
     538:	6e05                	lui	t3,0x1
     53a:	6d75                	lui	s10,0x1d
     53c:	9200                	.insn	2, 0x9200
     53e:	8619                	srai	a2,a2,0x6
     540:	0000                	unimp
     542:	0200                	addi	s0,sp,256
     544:	0418                	addi	a4,sp,512
     546:	1200                	addi	s0,sp,288
     548:	0000                	unimp
     54a:	0000                	unimp
     54c:	05ea                	slli	a1,a1,0x1a
     54e:	0000                	unimp
     550:	0101                	addi	sp,sp,0
     552:	0138015b          	.insn	4, 0x0138015b
     556:	5c01                	li	s8,-32
     558:	3001                	.insn	2, 0x3001
     55a:	0101                	addi	sp,sp,0
     55c:	015d                	addi	sp,sp,23
     55e:	0030                	addi	a2,sp,8
     560:	0400                	addi	s0,sp,512
     562:	00d9                	addi	ra,ra,22
     564:	0000                	unimp
     566:	0000043b          	addw	s0,zero,zero
     56a:	730a                	ld	t1,160(sp)
     56c:	7274                	ld	a3,224(a2)
     56e:	9700                	.insn	2, 0x9700
     570:	2a21                	addiw	s4,s4,8
     572:	0001                	nop
     574:	0100                	addi	s0,sp,128
     576:	0769                	addi	a4,a4,26
     578:	084a                	slli	a6,a6,0x12
     57a:	0000                	unimp
     57c:	03a2                	slli	t2,t2,0x8
     57e:	1200                	addi	s0,sp,288
     580:	0000                	unimp
     582:	0000                	unimp
     584:	0000e933          	or	s2,ra,zero
     588:	9800                	.insn	2, 0x9800
     58a:	2520                	fld	fs0,72(a0)
     58c:	0858                	addi	a4,sp,20
     58e:	0000                	unimp
     590:	6901                	.insn	2, 0x6901
     592:	6308                	ld	a0,0(a4)
     594:	0008                	.insn	2, 0x0008
     596:	d900                	sw	s0,48(a0)
     598:	0002                	c.slli64	zero
     59a:	d400                	sw	s0,40(s0)
     59c:	0002                	c.slli64	zero
     59e:	0f00                	addi	s0,sp,912
     5a0:	03bc                	addi	a5,sp,456
     5a2:	1200                	addi	s0,sp,288
     5a4:	0000                	unimp
     5a6:	0000                	unimp
     5a8:	08a0                	addi	s0,sp,88
     5aa:	0000                	unimp
     5ac:	0000                	unimp
     5ae:	2004                	fld	fs1,0(s0)
     5b0:	0001                	nop
     5b2:	6300                	ld	s0,0(a4)
     5b4:	0004                	.insn	2, 0x0004
     5b6:	0600                	addi	s0,sp,768
     5b8:	1a9c0063          	beq	s8,s1,758 <main-0x11fff8a8>
     5bc:	00de                	slli	ra,ra,0x17
     5be:	0000                	unimp
     5c0:	02ee                	slli	t0,t0,0x1b
     5c2:	0000                	unimp
     5c4:	02e9                	addi	t0,t0,26
     5c6:	0000                	unimp
     5c8:	0004860f          	.insn	4, 0x0004860f
     5cc:	0012                	c.slli	zero,0x4
     5ce:	0000                	unimp
     5d0:	a000                	fsd	fs0,0(s0)
     5d2:	0008                	.insn	2, 0x0008
     5d4:	0000                	unimp
     5d6:	f404                	sd	s1,40(s0)
     5d8:	0000                	unimp
     5da:	fc00                	sd	s0,56(s0)
     5dc:	0004                	.insn	2, 0x0004
     5de:	0a00                	addi	s0,sp,272
     5e0:	7470                	ld	a2,232(s0)
     5e2:	0072                	c.slli	zero,0x1c
     5e4:	1ba1                	addi	s7,s7,-24
     5e6:	05e8                	addi	a0,sp,716
     5e8:	0000                	unimp
     5ea:	6801                	.insn	2, 0x6801
     5ec:	4a10                	lw	a2,16(a2)
     5ee:	0008                	.insn	2, 0x0008
     5f0:	d800                	sw	s0,48(s0)
     5f2:	00120003          	lb	zero,1(tp) # 1 <main-0x11ffffff>
     5f6:	0000                	unimp
     5f8:	4800                	lw	s0,16(s0)
     5fa:	00ff 0000 20a2 04d8 	.insn	10, 0x04d820a2000000ff
     602:	0000 
     604:	5809                	li	a6,-30
     606:	0008                	.insn	2, 0x0008
     608:	0100                	addi	s0,sp,128
     60a:	ff000003          	lb	zero,-16(zero) # fffffffffffffff0 <__sheap+0xffffffffedffcff0>
     60e:	0002                	c.slli64	zero
     610:	0800                	addi	s0,sp,16
     612:	00000863          	beqz	zero,622 <main-0x11fff9de>
     616:	0312                	slli	t1,t1,0x4
     618:	0000                	unimp
     61a:	030e                	slli	t1,t1,0x3
     61c:	0000                	unimp
     61e:	e018                	sd	a4,0(s0)
     620:	00120003          	lb	zero,1(tp) # 1 <main-0x11ffffff>
     624:	0000                	unimp
     626:	a000                	fsd	fs0,0(s0)
     628:	0008                	.insn	2, 0x0008
     62a:	c300                	sw	s0,0(a4)
     62c:	0004                	.insn	2, 0x0004
     62e:	0100                	addi	s0,sp,128
     630:	5a01                	li	s4,-32
     632:	0802                	c.slli64	a6
     634:	0030                	addi	a2,sp,8
     636:	ec02                	sd	zero,24(sp)
     638:	00120003          	lb	zero,1(tp) # 1 <main-0x11ffffff>
     63c:	0000                	unimp
     63e:	a000                	fsd	fs0,0(s0)
     640:	0008                	.insn	2, 0x0008
     642:	0100                	addi	s0,sp,128
     644:	5a01                	li	s4,-32
     646:	0802                	c.slli64	a6
     648:	0078                	addi	a4,sp,12
     64a:	0200                	addi	s0,sp,256
     64c:	03fc                	addi	a5,sp,460
     64e:	1200                	addi	s0,sp,288
     650:	0000                	unimp
     652:	0000                	unimp
     654:	05ea                	slli	a1,a1,0x1a
     656:	0000                	unimp
     658:	0101                	addi	sp,sp,0
     65a:	025a                	slli	tp,tp,0x16
     65c:	0088                	addi	a0,sp,64
     65e:	0101                	addi	sp,sp,0
     660:	0140015b          	.insn	4, 0x0140015b
     664:	5c01                	li	s8,-32
     666:	3001                	.insn	2, 0x3001
     668:	0101                	addi	sp,sp,0
     66a:	015d                	addi	sp,sp,23
     66c:	0031                	c.nop	12
     66e:	1000                	addi	s0,sp,32
     670:	0000086f          	jal	a6,670 <main-0x11fff990>
     674:	04a4                	addi	s1,sp,584
     676:	1200                	addi	s0,sp,288
     678:	0000                	unimp
     67a:	0000                	unimp
     67c:	368e                	fld	fa3,224(sp)
     67e:	0001                	nop
     680:	a700                	fsd	fs0,8(a4)
     682:	6220                	ld	s0,64(a2)
     684:	0005                	c.nop	1
     686:	0900                	addi	s0,sp,144
     688:	087d                	addi	a6,a6,31
     68a:	0000                	unimp
     68c:	0000032b          	.insn	4, 0x032b
     690:	00000323          	sb	zero,6(zero) # 6 <main-0x11fffffa>
     694:	8719                	srai	a4,a4,0x6
     696:	0008                	.insn	2, 0x0008
     698:	6800                	ld	s0,16(s0)
     69a:	0005                	c.nop	1
     69c:	0012                	c.slli	zero,0x4
     69e:	0000                	unimp
     6a0:	c400                	sw	s0,8(s0)
     6a2:	0568                	addi	a0,sp,652
     6a4:	1200                	addi	s0,sp,288
     6a6:	0000                	unimp
     6a8:	0000                	unimp
     6aa:	001e                	c.slli	zero,0x7
     6ac:	0000                	unimp
     6ae:	0000                	unimp
     6b0:	0000                	unimp
     6b2:	9408                	.insn	2, 0x9408
     6b4:	0008                	.insn	2, 0x0008
     6b6:	4600                	lw	s0,8(a2)
     6b8:	3e000003          	lb	zero,992(zero) # 3e0 <main-0x11fffc20>
     6bc:	02000003          	lb	zero,32(zero) # 20 <main-0x11ffffe0>
     6c0:	0580                	addi	s0,sp,704
     6c2:	1200                	addi	s0,sp,288
     6c4:	0000                	unimp
     6c6:	0000                	unimp
     6c8:	0114                	addi	a3,sp,128
     6ca:	0000                	unimp
     6cc:	0101                	addi	sp,sp,0
     6ce:	025a                	slli	tp,tp,0x16
     6d0:	0088                	addi	a0,sp,64
     6d2:	0000                	unimp
     6d4:	0f00                	addi	s0,sp,912
     6d6:	033c                	addi	a5,sp,392
     6d8:	1200                	addi	s0,sp,288
     6da:	0000                	unimp
     6dc:	0000                	unimp
     6de:	08a0                	addi	s0,sp,88
     6e0:	0000                	unimp
     6e2:	7c18                	ld	a4,56(s0)
     6e4:	00120003          	lb	zero,1(tp) # 1 <main-0x11ffffff>
     6e8:	0000                	unimp
     6ea:	3000                	fld	fs0,32(s0)
     6ec:	0001                	nop
     6ee:	8e00                	.insn	2, 0x8e00
     6f0:	0005                	c.nop	1
     6f2:	0100                	addi	s0,sp,128
     6f4:	5a01                	li	s4,-32
     6f6:	0309                	addi	t1,t1,2
     6f8:	1088                	addi	a0,sp,96
     6fa:	1200                	addi	s0,sp,288
     6fc:	0000                	unimp
     6fe:	0000                	unimp
     700:	0200                	addi	s0,sp,256
     702:	045a                	slli	s0,s0,0x16
     704:	1200                	addi	s0,sp,288
     706:	0000                	unimp
     708:	0000                	unimp
     70a:	0130                	addi	a2,sp,136
     70c:	0000                	unimp
     70e:	0101                	addi	sp,sp,0
     710:	095a                	slli	s2,s2,0x16
     712:	00105803          	lhu	a6,1(zero) # 1 <main-0x11ffffff>
     716:	0012                	c.slli	zero,0x4
     718:	0000                	unimp
     71a:	0000                	unimp
     71c:	0700                	addi	s0,sp,896
     71e:	00000887          	.insn	4, 0x0887
     722:	0356                	slli	t1,t1,0x15
     724:	1200                	addi	s0,sp,288
     726:	0000                	unimp
     728:	0000                	unimp
     72a:	461e                	lw	a2,196(sp)
     72c:	0001                	nop
     72e:	b300                	fsd	fs0,32(a4)
     730:	0805                	addi	a6,a6,1
     732:	0894                	addi	a3,sp,80
     734:	0000                	unimp
     736:	00000367          	jalr	t1,zero # 0 <main-0x12000000>
     73a:	035d                	addi	t1,t1,23
     73c:	0000                	unimp
     73e:	e602                	sd	zero,264(sp)
     740:	0004                	.insn	2, 0x0004
     742:	0012                	c.slli	zero,0x4
     744:	0000                	unimp
     746:	1400                	addi	s0,sp,544
     748:	0001                	nop
     74a:	0100                	addi	s0,sp,128
     74c:	5a01                	li	s4,-32
     74e:	0309                	addi	t1,t1,2
     750:	2000                	fld	fs0,0(s0)
     752:	1200                	addi	s0,sp,288
     754:	0000                	unimp
     756:	0000                	unimp
     758:	0000                	unimp
     75a:	2600                	fld	fs0,8(a2)
     75c:	2708                	fld	fa0,8(a4)
     75e:	01c2                	slli	gp,gp,0x10
     760:	0000                	unimp
     762:	3001                	.insn	2, 0x3001
     764:	b601                	j	264 <main-0x11fffd9c>
     766:	0000                	unimp
     768:	c200                	sw	s0,0(a2)
     76a:	0000                	unimp
     76c:	0012                	c.slli	zero,0x4
     76e:	0000                	unimp
     770:	0c00                	addi	s0,sp,528
     772:	0002                	c.slli64	zero
     774:	0000                	unimp
     776:	0000                	unimp
     778:	0100                	addi	s0,sp,128
     77a:	339c                	fld	fa5,32(a5)
     77c:	0008                	.insn	2, 0x0008
     77e:	0b00                	addi	s0,sp,400
     780:	756e                	ld	a0,248(sp)
     782:	006d                	c.nop	27
     784:	0f30                	addi	a2,sp,920
     786:	00000097          	auipc	ra,0x0
     78a:	039d                	addi	t2,t2,7
     78c:	0000                	unimp
     78e:	0385                	addi	t2,t2,1
     790:	0000                	unimp
     792:	fe1a                	sd	t1,312(sp)
     794:	0001                	nop
     796:	1700                	addi	s0,sp,928
     798:	00000053          	fadd.s	ft0,ft0,ft0,rne
     79c:	03fa                	slli	t2,t2,0x1e
     79e:	0000                	unimp
     7a0:	03e2                	slli	t2,t2,0x18
     7a2:	0000                	unimp
     7a4:	7a1a                	ld	s4,416(sp)
     7a6:	0001                	nop
     7a8:	2200                	fld	fs0,0(a2)
     7aa:	00000833          	add	a6,zero,zero
     7ae:	00000457          	.insn	4, 0x0457
     7b2:	0000043f 6461700b 	.insn	8, 0x6461700b0000043f
     7ba:	3000                	fld	fs0,32(s0)
     7bc:	3332                	fld	ft6,296(sp)
     7be:	0008                	.insn	2, 0x0008
     7c0:	be00                	fsd	fs0,56(a2)
     7c2:	0004                	.insn	2, 0x0004
     7c4:	9c00                	.insn	2, 0x9c00
     7c6:	0004                	.insn	2, 0x0004
     7c8:	1400                	addi	s0,sp,544
     7ca:	0155                	addi	sp,sp,21
     7cc:	0000                	unimp
     7ce:	1831                	addi	a6,a6,-20
     7d0:	012a                	slli	sp,sp,0xa
     7d2:	0000                	unimp
     7d4:	030a                	slli	t1,t1,0x2
     7d6:	1038                	addi	a4,sp,40
     7d8:	1200                	addi	s0,sp,288
     7da:	0000                	unimp
     7dc:	0000                	unimp
     7de:	0c9f 01d2 0000      	.insn	6, 0x01d20c9f
     7e4:	00860937          	lui	s2,0x860
     7e8:	0000                	unimp
     7ea:	0531                	addi	a0,a0,12
     7ec:	0000                	unimp
     7ee:	0514                	addi	a3,sp,640
     7f0:	0000                	unimp
     7f2:	ef0c                	sd	a1,24(a4)
     7f4:	0001                	nop
     7f6:	3800                	fld	fs0,48(s0)
     7f8:	de0a                	sw	sp,60(sp)
     7fa:	0000                	unimp
     7fc:	a800                	fsd	fs0,16(s0)
     7fe:	0005                	c.nop	1
     800:	9b00                	.insn	2, 0x9b00
     802:	0005                	c.nop	1
     804:	0a00                	addi	s0,sp,272
     806:	7562                	ld	a0,56(sp)
     808:	0066                	c.slli	zero,0x19
     80a:	0a45                	addi	s4,s4,17
     80c:	083a                	slli	a6,a6,0xe
     80e:	0000                	unimp
     810:	7f889103          	lh	sp,2040(a7)
     814:	6906                	ld	s2,64(sp)
     816:	4600                	lw	s0,8(a2)
     818:	0000b60b          	.insn	4, 0xb60b
     81c:	df00                	sw	s0,56(a4)
     81e:	0005                	c.nop	1
     820:	d200                	sw	s0,32(a2)
     822:	0005                	c.nop	1
     824:	0c00                	addi	s0,sp,528
     826:	01ae                	slli	gp,gp,0xb
     828:	0000                	unimp
     82a:	0b4d                	addi	s6,s6,19
     82c:	00b6                	slli	ra,ra,0xd
     82e:	0000                	unimp
     830:	0619                	addi	a2,a2,6
     832:	0000                	unimp
     834:	0606                	slli	a2,a2,0x1
     836:	0000                	unimp
     838:	6e0c                	ld	a1,24(a2)
     83a:	0001                	nop
     83c:	5200                	lw	s0,32(a2)
     83e:	7f09                	lui	t5,0xfffe2
     840:	0000                	unimp
     842:	5900                	lw	s0,48(a0)
     844:	0006                	c.slli	zero,0x1
     846:	4800                	lw	s0,16(s0)
     848:	0006                	c.slli	zero,0x1
     84a:	0400                	addi	s0,sp,512
     84c:	004a                	c.slli	zero,0x12
     84e:	0000                	unimp
     850:	0752                	slli	a4,a4,0x14
     852:	0000                	unimp
     854:	6b06                	ld	s6,64(sp)
     856:	5900                	lw	s0,48(a0)
     858:	7f12                	ld	t5,288(sp)
     85a:	0000                	unimp
     85c:	9500                	.insn	2, 0x9500
     85e:	0006                	c.slli	zero,0x1
     860:	8900                	.insn	2, 0x8900
     862:	0006                	c.slli	zero,0x1
     864:	0700                	addi	s0,sp,896
     866:	0000086f          	jal	a6,866 <main-0x11fff79a>
     86a:	0166                	slli	sp,sp,0x19
     86c:	1200                	addi	s0,sp,288
     86e:	0000                	unimp
     870:	0000                	unimp
     872:	5539                	li	a0,-18
     874:	0000                	unimp
     876:	5a00                	lw	s0,48(a2)
     878:	091c                	addi	a5,sp,144
     87a:	087d                	addi	a6,a6,31
     87c:	0000                	unimp
     87e:	06ce                	slli	a3,a3,0x13
     880:	0000                	unimp
     882:	06ca                	slli	a3,a3,0x12
     884:	0000                	unimp
     886:	00088707          	.insn	4, 0x00088707
     88a:	6600                	ld	s0,8(a2)
     88c:	0001                	nop
     88e:	0012                	c.slli	zero,0x4
     890:	0000                	unimp
     892:	3c00                	fld	fs0,56(s0)
     894:	0079                	c.nop	30
     896:	0000                	unimp
     898:	0918                	addi	a4,sp,144
     89a:	9408                	.insn	2, 0x9408
     89c:	0008                	.insn	2, 0x0008
     89e:	e500                	sd	s0,8(a0)
     8a0:	0006                	c.slli	zero,0x1
     8a2:	e100                	sd	s0,0(a0)
     8a4:	0006                	c.slli	zero,0x1
     8a6:	0200                	addi	s0,sp,256
     8a8:	018e                	slli	gp,gp,0x3
     8aa:	1200                	addi	s0,sp,288
     8ac:	0000                	unimp
     8ae:	0000                	unimp
     8b0:	0114                	addi	a3,sp,128
     8b2:	0000                	unimp
     8b4:	0101                	addi	sp,sp,0
     8b6:	095a                	slli	s2,s2,0x16
     8b8:	00200003          	lb	zero,2(zero) # 2 <main-0x11fffffe>
     8bc:	0012                	c.slli	zero,0x4
     8be:	0000                	unimp
     8c0:	0000                	unimp
     8c2:	0000                	unimp
     8c4:	0400                	addi	s0,sp,512
     8c6:	0084                	addi	s1,sp,64
     8c8:	0000                	unimp
     8ca:	077a                	slli	a4,a4,0x1e
     8cc:	0000                	unimp
     8ce:	6a06                	ld	s4,64(sp)
     8d0:	5e00                	lw	s0,56(a2)
     8d2:	b610                	fsd	fa2,40(a2)
     8d4:	0000                	unimp
     8d6:	0c00                	addi	s0,sp,528
     8d8:	04000007          	.insn	4, 0x04000007
     8dc:	0f000007          	.insn	4, 0x0f000007
     8e0:	01dc                	addi	a5,sp,196
     8e2:	1200                	addi	s0,sp,288
     8e4:	0000                	unimp
     8e6:	0000                	unimp
     8e8:	08a0                	addi	s0,sp,88
     8ea:	0000                	unimp
     8ec:	1000                	addi	s0,sp,32
     8ee:	0000086f          	jal	a6,8ee <main-0x11fff712>
     8f2:	0248                	addi	a0,sp,260
     8f4:	1200                	addi	s0,sp,288
     8f6:	0000                	unimp
     8f8:	0000                	unimp
     8fa:	0000358f          	.insn	4, 0x358f
     8fe:	4200                	lw	s0,0(a2)
     900:	e110                	sd	a2,0(a0)
     902:	09000007          	.insn	4, 0x09000007
     906:	087d                	addi	a6,a6,31
     908:	0000                	unimp
     90a:	0000072b          	.insn	4, 0x072b
     90e:	0724                	addi	s1,sp,904
     910:	0000                	unimp
     912:	8719                	srai	a4,a4,0x6
     914:	0008                	.insn	2, 0x0008
     916:	ac00                	fsd	fs0,24(s0)
     918:	0002                	c.slli64	zero
     91a:	0012                	c.slli	zero,0x4
     91c:	0000                	unimp
     91e:	ac00                	fsd	fs0,24(s0)
     920:	02ac                	addi	a1,sp,328
     922:	1200                	addi	s0,sp,288
     924:	0000                	unimp
     926:	0000                	unimp
     928:	0022                	c.slli	zero,0x8
     92a:	0000                	unimp
     92c:	0000                	unimp
     92e:	0000                	unimp
     930:	9408                	.insn	2, 0x9408
     932:	0008                	.insn	2, 0x0008
     934:	4600                	lw	s0,8(a2)
     936:	3e000007          	.insn	4, 0x3e000007
     93a:	02000007          	.insn	4, 0x02000007
     93e:	02c6                	slli	t0,t0,0x11
     940:	1200                	addi	s0,sp,288
     942:	0000                	unimp
     944:	0000                	unimp
     946:	0114                	addi	a3,sp,128
     948:	0000                	unimp
     94a:	0101                	addi	sp,sp,0
     94c:	035a                	slli	t1,t1,0x16
     94e:	0072                	c.slli	zero,0x1c
     950:	0006                	c.slli	zero,0x1
     952:	0000                	unimp
     954:	00086f07          	.insn	4, 0x00086f07
     958:	1c00                	addi	s0,sp,560
     95a:	0002                	c.slli64	zero
     95c:	0012                	c.slli	zero,0x4
     95e:	0000                	unimp
     960:	7f00                	ld	s0,56(a4)
     962:	0000008f          	.insn	4, 0x008f
     966:	1854                	addi	a3,sp,52
     968:	7d09                	lui	s10,0xfffe2
     96a:	0008                	.insn	2, 0x0008
     96c:	6400                	ld	s0,8(s0)
     96e:	5d000007          	.insn	4, 0x5d000007
     972:	07000007          	.insn	4, 0x07000007
     976:	00000887          	.insn	4, 0x0887
     97a:	0290                	addi	a2,sp,320
     97c:	1200                	addi	s0,sp,288
     97e:	0000                	unimp
     980:	0000                	unimp
     982:	a4a2                	fsd	fs0,72(sp)
     984:	0000                	unimp
     986:	1800                	addi	s0,sp,48
     988:	1b09                	addi	s6,s6,-30
     98a:	0894                	addi	a3,sp,80
     98c:	0000                	unimp
     98e:	9e02                	jalr	t3
     990:	0002                	c.slli64	zero
     992:	0012                	c.slli	zero,0x4
     994:	0000                	unimp
     996:	1400                	addi	s0,sp,544
     998:	0001                	nop
     99a:	0100                	addi	s0,sp,128
     99c:	5a01                	li	s4,-32
     99e:	06007203          	.insn	4, 0x06007203
     9a2:	0000                	unimp
     9a4:	0000                	unimp
     9a6:	89020103          	lb	sp,-1904(tp) # fffffffffffff890 <__sheap+0xffffffffedffc890>
     9aa:	0001                	nop
     9ac:	1200                	addi	s0,sp,288
     9ae:	00de                	slli	ra,ra,0x17
     9b0:	0000                	unimp
     9b2:	084a                	slli	a6,a6,0x12
     9b4:	0000                	unimp
     9b6:	00002e13          	slti	t3,zero,0
     9ba:	4000                	lw	s0,0(s0)
     9bc:	1c00                	addi	s0,sp,560
     9be:	01f4                	addi	a3,sp,204
     9c0:	0000                	unimp
     9c2:	b622                	fsd	fs0,296(sp)
     9c4:	0000                	unimp
     9c6:	6f00                	ld	s0,24(a4)
     9c8:	0008                	.insn	2, 0x0008
     9ca:	1d00                	addi	s0,sp,688
     9cc:	00727473          	csrrci	s0,0x7,4
     9d0:	1722                	slli	a4,a4,0x28
     9d2:	012a                	slli	sp,sp,0xa
     9d4:	0000                	unimp
     9d6:	6c05                	lui	s8,0x1
     9d8:	6e65                	lui	t3,0x19
     9da:	2700                	fld	fs0,8(a4)
     9dc:	0000b60b          	.insn	4, 0xb60b
     9e0:	0000                	unimp
     9e2:	841c                	.insn	2, 0x841c
     9e4:	0001                	nop
     9e6:	1600                	addi	s0,sp,800
     9e8:	00b6                	slli	ra,ra,0xd
     9ea:	0000                	unimp
     9ec:	00000887          	.insn	4, 0x0887
     9f0:	631d                	lui	t1,0x7
     9f2:	1600                	addi	s0,sp,800
     9f4:	0000de0b          	.insn	4, 0xde0b
     9f8:	0000                	unimp
     9fa:	cc28                	sw	a0,88(s0)
     9fc:	0001                	nop
     9fe:	0100                	addi	s0,sp,128
     a00:	010c                	addi	a1,sp,128
     a02:	a001                	j	a02 <main-0x11fff5fe>
     a04:	0008                	.insn	2, 0x0008
     a06:	0500                	addi	s0,sp,640
     a08:	656c                	ld	a1,200(a0)
     a0a:	006e                	c.slli	zero,0x1b
     a0c:	0b0d                	addi	s6,s6,3
     a0e:	00b6                	slli	ra,ra,0xd
     a10:	0000                	unimp
     a12:	2900                	fld	fs0,16(a0)
     a14:	0000086f          	jal	a6,a14 <main-0x11fff5ec>
     a18:	0040                	addi	s0,sp,4
     a1a:	1200                	addi	s0,sp,288
     a1c:	0000                	unimp
     a1e:	0000                	unimp
     a20:	0082                	c.slli64	ra
     a22:	0000                	unimp
     a24:	0000                	unimp
     a26:	0000                	unimp
     a28:	9c01                	subw	s0,s0,s0
     a2a:	0939                	addi	s2,s2,14 # 86000e <main-0x1179fff2>
     a2c:	0000                	unimp
     a2e:	7d09                	lui	s10,0xfffe2
     a30:	0008                	.insn	2, 0x0008
     a32:	8100                	.insn	2, 0x8100
     a34:	77000007          	.insn	4, 0x77000007
     a38:	10000007          	.insn	4, 0x10000007
     a3c:	00000887          	.insn	4, 0x0887
     a40:	0068                	addi	a0,sp,12
     a42:	1200                	addi	s0,sp,288
     a44:	0000                	unimp
     a46:	0000                	unimp
     a48:	230c                	fld	fa1,0(a4)
     a4a:	0000                	unimp
     a4c:	1c00                	addi	s0,sp,560
     a4e:	0909                	addi	s2,s2,2
     a50:	0009                	c.nop	2
     a52:	0800                	addi	s0,sp,16
     a54:	0894                	addi	a3,sp,80
     a56:	0000                	unimp
     a58:	07a4                	addi	s1,sp,968
     a5a:	0000                	unimp
     a5c:	07a2                	slli	a5,a5,0x8
     a5e:	0000                	unimp
     a60:	b802                	fsd	ft0,48(sp)
     a62:	0000                	unimp
     a64:	0012                	c.slli	zero,0x4
     a66:	0000                	unimp
     a68:	1400                	addi	s0,sp,544
     a6a:	0001                	nop
     a6c:	0100                	addi	s0,sp,128
     a6e:	5a01                	li	s4,-32
     a70:	0309                	addi	t1,t1,2 # 7002 <main-0x11ff8ffe>
     a72:	2000                	fld	fs0,0(s0)
     a74:	1200                	addi	s0,sp,288
     a76:	0000                	unimp
     a78:	0000                	unimp
     a7a:	0000                	unimp
     a7c:	00088707          	.insn	4, 0x00088707
     a80:	8800                	.insn	2, 0x8800
     a82:	0000                	unimp
     a84:	0012                	c.slli	zero,0x4
     a86:	0000                	unimp
     a88:	1500                	addi	s0,sp,672
     a8a:	002e                	c.slli	zero,0xb
     a8c:	0000                	unimp
     a8e:	0918                	addi	a4,sp,144
     a90:	0008941b          	slliw	s0,a7,0x0
     a94:	0200                	addi	s0,sp,256
     a96:	0098                	addi	a4,sp,64
     a98:	1200                	addi	s0,sp,288
     a9a:	0000                	unimp
     a9c:	0000                	unimp
     a9e:	0114                	addi	a3,sp,128
     aa0:	0000                	unimp
     aa2:	0101                	addi	sp,sp,0
     aa4:	035a                	slli	t1,t1,0x16
     aa6:	0072                	c.slli	zero,0x1c
     aa8:	0006                	c.slli	zero,0x1
     aaa:	0000                	unimp
     aac:	052a                	slli	a0,a0,0xa
     aae:	039e                	slli	t2,t2,0x7
     ab0:	7830                	ld	a2,112(s0)
     ab2:	0000                	unimp
     ab4:	02a6                	slli	t0,t0,0x9
     ab6:	0000                	unimp
     ab8:	0005                	c.nop	1
     aba:	0801                	addi	a6,a6,0
     abc:	0365                	addi	t1,t1,25
     abe:	0000                	unimp
     ac0:	2b09                	addiw	s6,s6,2
     ac2:	0000                	unimp
     ac4:	1d00                	addi	s0,sp,688
     ac6:	00a6                	slli	ra,ra,0x9
     ac8:	0000                	unimp
     aca:	015e                	slli	sp,sp,0x17
     acc:	0000                	unimp
     ace:	05ba                	slli	a1,a1,0xe
     ad0:	1200                	addi	s0,sp,288
     ad2:	0000                	unimp
     ad4:	0000                	unimp
     ad6:	0028                	addi	a0,sp,8
     ad8:	0000                	unimp
     ada:	0000                	unimp
     adc:	0000                	unimp
     ade:	00000dcf          	fnmadd.s	fs11,ft0,ft0,ft0,rne
     ae2:	0101                	addi	sp,sp,0
     ae4:	0b08                	addi	a0,sp,400
     ae6:	0001                	nop
     ae8:	0100                	addi	s0,sp,128
     aea:	0601                	addi	a2,a2,0
     aec:	010d                	addi	sp,sp,3
     aee:	0000                	unimp
     af0:	0201                	addi	tp,tp,0 # 0 <main-0x12000000>
     af2:	00012d07          	flw	fs10,0(sp)
     af6:	0100                	addi	s0,sp,128
     af8:	0502                	c.slli64	a0
     afa:	0000014b          	fnmsub.s	ft2,ft0,ft0,ft0,rne
     afe:	0401                	addi	s0,s0,0 # ffffffffffff9000 <__sheap+0xffffffffedff6000>
     b00:	00001e07          	.insn	4, 0x1e07
     b04:	0a00                	addi	s0,sp,272
     b06:	0504                	addi	s1,sp,640
     b08:	6e69                	lui	t3,0x1a
     b0a:	0074                	addi	a3,sp,12
     b0c:	7506                	ld	a0,96(sp)
     b0e:	3436                	fld	fs0,360(sp)
     b10:	3d00                	fld	fs0,56(a0)
     b12:	0062                	c.slli	zero,0x18
     b14:	0000                	unimp
     b16:	0801                	addi	a6,a6,0
     b18:	00001407          	.insn	4, 0x1407
     b1c:	0600                	addi	s0,sp,768
     b1e:	3669                	addiw	a2,a2,-6
     b20:	0034                	addi	a3,sp,8
     b22:	733e                	ld	t1,488(sp)
     b24:	0000                	unimp
     b26:	0100                	addi	s0,sp,128
     b28:	0508                	addi	a0,sp,640
     b2a:	0000                	unimp
     b2c:	0000                	unimp
     b2e:	0401                	addi	s0,s0,0
     b30:	4504                	lw	s1,8(a0)
     b32:	0001                	nop
     b34:	0100                	addi	s0,sp,128
     b36:	0408                	addi	a0,sp,512
     b38:	0119                	addi	sp,sp,6
     b3a:	0000                	unimp
     b3c:	0001e907          	.insn	4, 0x0001e907
     b40:	4200                	lw	s0,0(a2)
     b42:	0058                	addi	a4,sp,4
     b44:	0000                	unimp
     b46:	00000e07          	.insn	4, 0x0e07
     b4a:	4300                	lw	s0,0(a4)
     b4c:	0069                	c.nop	26
     b4e:	0000                	unimp
     b50:	00023c0b          	.insn	4, 0x00023c0b
     b54:	0500                	addi	s0,sp,640
     b56:	090d                	addi	s2,s2,3
     b58:	0088                	addi	a0,sp,64
     b5a:	0000                	unimp
     b5c:	00b2                	slli	ra,ra,0xc
     b5e:	0000                	unimp
     b60:	b20c                	fsd	fa1,32(a2)
     b62:	0000                	unimp
     b64:	0000                	unimp
     b66:	080d                	addi	a6,a6,3
     b68:	000000bf 14080101 	.insn	8, 0x14080101000000bf
     b70:	0001                	nop
     b72:	0e00                	addi	s0,sp,784
     b74:	00b8                	addi	a4,sp,72
     b76:	0000                	unimp
     b78:	0001da0f          	.insn	4, 0x0001da0f
     b7c:	0100                	addi	s0,sp,128
     b7e:	00880107          	.insn	4, 0x00880107
     b82:	0000                	unimp
     b84:	05ba                	slli	a1,a1,0xe
     b86:	1200                	addi	s0,sp,288
     b88:	0000                	unimp
     b8a:	0000                	unimp
     b8c:	0028                	addi	a0,sp,8
     b8e:	0000                	unimp
     b90:	0000                	unimp
     b92:	0000                	unimp
     b94:	9c01                	subw	s0,s0,s0
     b96:	01fd                	addi	gp,gp,31
     b98:	0000                	unimp
     b9a:	7310                	ld	a2,32(a4)
     b9c:	7274                	ld	a3,224(a2)
     b9e:	0100                	addi	s0,sp,128
     ba0:	00b21407          	.insn	4, 0x00b21407
     ba4:	0000                	unimp
     ba6:	07c8                	addi	a0,sp,964
     ba8:	0000                	unimp
     baa:	07c2                	slli	a5,a5,0x10
     bac:	0000                	unimp
     bae:	6c11                	lui	s8,0x4
     bb0:	6e65                	lui	t3,0x19
     bb2:	0100                	addi	s0,sp,128
     bb4:	0b08                	addi	a0,sp,400
     bb6:	0088                	addi	a0,sp,64
     bb8:	0000                	unimp
     bba:	07df 0000 07db      	.insn	6, 0x07db000007df
     bc0:	0000                	unimp
     bc2:	fd12                	sd	tp,184(sp)
     bc4:	0001                	nop
     bc6:	cc00                	sw	s0,24(s0)
     bc8:	0005                	c.nop	1
     bca:	0012                	c.slli	zero,0x4
     bcc:	0000                	unimp
     bce:	0700                	addi	s0,sp,896
     bd0:	05cc                	addi	a1,sp,708
     bd2:	1200                	addi	s0,sp,288
     bd4:	0000                	unimp
     bd6:	0000                	unimp
     bd8:	000e                	c.slli	zero,0x3
     bda:	0000                	unimp
     bdc:	0000                	unimp
     bde:	0000                	unimp
     be0:	0901                	addi	s2,s2,0
     be2:	e80c                	sd	a1,16(s0)
     be4:	0001                	nop
     be6:	0200                	addi	s0,sp,256
     be8:	020e                	slli	tp,tp,0x3
     bea:	0000                	unimp
     bec:	07ec                	addi	a1,sp,972
     bee:	0000                	unimp
     bf0:	07ea                	slli	a5,a5,0x1a
     bf2:	0000                	unimp
     bf4:	1802                	slli	a6,a6,0x20
     bf6:	0002                	c.slli64	zero
     bf8:	f600                	sd	s0,40(a2)
     bfa:	f2000007          	.insn	4, 0xf2000007
     bfe:	13000007          	.insn	4, 0x13000007
     c02:	00000223          	sb	zero,4(zero) # 4 <main-0x11fffffc>
     c06:	05cc                	addi	a1,sp,708
     c08:	1200                	addi	s0,sp,288
     c0a:	0000                	unimp
     c0c:	0000                	unimp
     c0e:	cc09                	beqz	s0,c28 <main-0x11fff3d8>
     c10:	0005                	c.nop	1
     c12:	0012                	c.slli	zero,0x4
     c14:	0000                	unimp
     c16:	0e00                	addi	s0,sp,784
     c18:	0000                	unimp
     c1a:	0000                	unimp
     c1c:	0000                	unimp
     c1e:	0200                	addi	s0,sp,256
     c20:	0c21                	addi	s8,s8,8 # 4008 <main-0x11ffbff8>
     c22:	3002                	fld	ft0,32(sp)
     c24:	0002                	c.slli64	zero
     c26:	0300                	addi	s0,sp,384
     c28:	0008                	.insn	2, 0x0008
     c2a:	0100                	addi	s0,sp,128
     c2c:	0008                	.insn	2, 0x0008
     c2e:	0200                	addi	s0,sp,256
     c30:	0000023b          	addw	tp,zero,zero
     c34:	080c                	addi	a1,sp,16
     c36:	0000                	unimp
     c38:	080a                	slli	a6,a6,0x2
     c3a:	0000                	unimp
     c3c:	4602                	lw	a2,0(sp)
     c3e:	0002                	c.slli64	zero
     c40:	1600                	addi	s0,sp,800
     c42:	0008                	.insn	2, 0x0008
     c44:	1200                	addi	s0,sp,288
     c46:	0008                	.insn	2, 0x0008
     c48:	0200                	addi	s0,sp,256
     c4a:	0251                	addi	tp,tp,20 # 14 <main-0x11ffffec>
     c4c:	0000                	unimp
     c4e:	00000823          	sb	zero,16(zero) # 10 <main-0x11fffff0>
     c52:	0821                	addi	a6,a6,8
     c54:	0000                	unimp
     c56:	5c02                	lw	s8,32(sp)
     c58:	0002                	c.slli64	zero
     c5a:	2300                	fld	fs0,0(a4)
     c5c:	0008                	.insn	2, 0x0008
     c5e:	2100                	fld	fs0,0(a0)
     c60:	0008                	.insn	2, 0x0008
     c62:	0200                	addi	s0,sp,256
     c64:	00000267          	jalr	tp,zero # 0 <main-0x12000000>
     c68:	00000823          	sb	zero,16(zero) # 10 <main-0x11fffff0>
     c6c:	0821                	addi	a6,a6,8
     c6e:	0000                	unimp
     c70:	00027203          	.insn	4, 0x00027203
     c74:	0100                	addi	s0,sp,128
     c76:	035a                	slli	t1,t1,0x16
     c78:	0000027b          	.insn	4, 0x027b
     c7c:	5b01                	li	s6,-32
     c7e:	00028403          	lb	s0,0(t0)
     c82:	0100                	addi	s0,sp,128
     c84:	035c                	addi	a5,sp,388
     c86:	028d                	addi	t0,t0,3
     c88:	0000                	unimp
     c8a:	5d01                	li	s10,-32
     c8c:	00029603          	lh	a2,0(t0)
     c90:	0100                	addi	s0,sp,128
     c92:	035e                	slli	t1,t1,0x17
     c94:	029f 0000 6101      	.insn	6, 0x61010000029f
     c9a:	0000                	unimp
     c9c:	ca14                	sw	a3,16(a2)
     c9e:	0005                	c.nop	1
     ca0:	0012                	c.slli	zero,0x4
     ca2:	0000                	unimp
     ca4:	9c00                	.insn	2, 0x9c00
     ca6:	0000                	unimp
     ca8:	1500                	addi	s0,sp,672
     caa:	5a01                	li	s4,-32
     cac:	7802                	ld	a6,32(sp)
     cae:	0000                	unimp
     cb0:	1600                	addi	s0,sp,800
     cb2:	0000022f          	.insn	4, 0x022f
     cb6:	2002                	fld	ft0,0(sp)
     cb8:	9201                	srli	a2,a2,0x20
     cba:	0000                	unimp
     cbc:	0300                	addi	s0,sp,384
     cbe:	00000223          	sb	zero,4(zero) # 4 <main-0x11fffffc>
     cc2:	7308                	ld	a0,32(a4)
     cc4:	7274                	ld	a3,224(a2)
     cc6:	1a00                	addi	s0,sp,304
     cc8:	00b2                	slli	ra,ra,0xc
     cca:	0000                	unimp
     ccc:	6c08                	ld	a0,24(s0)
     cce:	6e65                	lui	t3,0x19
     cd0:	2500                	fld	fs0,8(a0)
     cd2:	0088                	addi	a0,sp,64
     cd4:	0000                	unimp
     cd6:	1700                	addi	s0,sp,928
     cd8:	0222                	slli	tp,tp,0x8
     cda:	0000                	unimp
     cdc:	58010503          	lb	a0,1408(sp)
     ce0:	0000                	unimp
     ce2:	0300                	addi	s0,sp,384
     ce4:	0d04                	addi	s1,sp,656
     ce6:	0002                	c.slli64	zero
     ce8:	0600                	addi	s0,sp,768
     cea:	0000880b          	.insn	4, 0x880b
     cee:	0400                	addi	s0,sp,512
     cf0:	00000203          	lb	tp,0(zero) # 0 <main-0x12000000>
     cf4:	00580907          	.insn	4, 0x00580907
     cf8:	0000                	unimp
     cfa:	1304                	addi	s1,sp,416
     cfc:	0002                	c.slli64	zero
     cfe:	0800                	addi	s0,sp,16
     d00:	5809                	li	a6,-30
     d02:	0000                	unimp
     d04:	0400                	addi	s0,sp,512
     d06:	0218                	addi	a4,sp,256
     d08:	0000                	unimp
     d0a:	0909                	addi	s2,s2,2
     d0c:	0058                	addi	a4,sp,4
     d0e:	0000                	unimp
     d10:	0804                	addi	s1,sp,16
     d12:	0002                	c.slli64	zero
     d14:	0a00                	addi	s0,sp,272
     d16:	5809                	li	a6,-30
     d18:	0000                	unimp
     d1a:	0400                	addi	s0,sp,512
     d1c:	021d                	addi	tp,tp,7 # 7 <main-0x11fffff9>
     d1e:	0000                	unimp
     d20:	0058090b          	.insn	4, 0x0058090b
     d24:	0000                	unimp
     d26:	6105                	addi	sp,sp,32
     d28:	0030                	addi	a2,sp,8
     d2a:	580d                	li	a6,-29
     d2c:	0000                	unimp
     d2e:	0500                	addi	s0,sp,640
     d30:	3161                	addiw	sp,sp,-8
     d32:	0e00                	addi	s0,sp,784
     d34:	0058                	addi	a4,sp,4
     d36:	0000                	unimp
     d38:	6105                	addi	sp,sp,32
     d3a:	0032                	c.slli	zero,0xc
     d3c:	0000580f          	.insn	4, 0x580f
     d40:	0500                	addi	s0,sp,640
     d42:	3361                	addiw	t1,t1,-8
     d44:	1000                	addi	s0,sp,32
     d46:	0058                	addi	a4,sp,4
     d48:	0000                	unimp
     d4a:	6105                	addi	sp,sp,32
     d4c:	0034                	addi	a3,sp,8
     d4e:	5811                	li	a6,-28
     d50:	0000                	unimp
     d52:	0500                	addi	s0,sp,640
     d54:	3761                	addiw	a4,a4,-8
     d56:	1200                	addi	s0,sp,288
     d58:	0058                	addi	a4,sp,4
     d5a:	0000                	unimp
     d5c:	0000                	unimp
     d5e:	019e                	slli	gp,gp,0x7
     d60:	0000                	unimp
     d62:	0005                	c.nop	1
     d64:	0801                	addi	a6,a6,0
     d66:	000004d3          	fadd.s	fs1,ft0,ft0,rne
     d6a:	2b09                	addiw	s6,s6,2
     d6c:	0000                	unimp
     d6e:	1d00                	addi	s0,sp,688
     d70:	019f 0000 015e      	.insn	6, 0x015e0000019f
     d76:	0000                	unimp
     d78:	05e2                	slli	a1,a1,0x18
     d7a:	1200                	addi	s0,sp,288
     d7c:	0000                	unimp
     d7e:	0000                	unimp
     d80:	004c                	addi	a1,sp,4
     d82:	0000                	unimp
     d84:	0000                	unimp
     d86:	0000                	unimp
     d88:	0ee8                	addi	a0,sp,860
     d8a:	0000                	unimp
     d8c:	9f02                	jalr	t5
     d8e:	0001                	nop
     d90:	0200                	addi	s0,sp,256
     d92:	1b28                	addi	a0,sp,440
     d94:	003a                	c.slli	zero,0xe
     d96:	0000                	unimp
     d98:	080a                	slli	a6,a6,0x2
     d9a:	015c                	addi	a5,sp,132
     d9c:	0000                	unimp
     d9e:	a602                	fsd	ft0,264(sp)
     da0:	0001                	nop
     da2:	0200                	addi	s0,sp,256
     da4:	002e1867          	.insn	4, 0x002e1867
     da8:	0000                	unimp
     daa:	0101                	addi	sp,sp,0
     dac:	0b08                	addi	a0,sp,400
     dae:	0001                	nop
     db0:	0100                	addi	s0,sp,128
     db2:	0601                	addi	a2,a2,0
     db4:	010d                	addi	sp,sp,3
     db6:	0000                	unimp
     db8:	0201                	addi	tp,tp,0 # 0 <main-0x12000000>
     dba:	00012d07          	flw	fs10,0(sp)
     dbe:	0100                	addi	s0,sp,128
     dc0:	0502                	c.slli64	a0
     dc2:	0000014b          	fnmsub.s	ft2,ft0,ft0,ft0,rne
     dc6:	0401                	addi	s0,s0,0
     dc8:	00001e07          	.insn	4, 0x1e07
     dcc:	0b00                	addi	s0,sp,400
     dce:	0504                	addi	s1,sp,640
     dd0:	6e69                	lui	t3,0x1a
     dd2:	0074                	addi	a3,sp,12
     dd4:	0801                	addi	a6,a6,0
     dd6:	00001407          	.insn	4, 0x1407
     dda:	0c00                	addi	s0,sp,528
     ddc:	3669                	addiw	a2,a2,-6
     dde:	0034                	addi	a3,sp,8
     de0:	891d3e03          	ld	t3,-1903(s10) # fffffffffffe1891 <__sheap+0xffffffffedfde891>
     de4:	0000                	unimp
     de6:	0100                	addi	s0,sp,128
     de8:	0508                	addi	a0,sp,640
     dea:	0000                	unimp
     dec:	0000                	unimp
     dee:	0401                	addi	s0,s0,0
     df0:	4504                	lw	s1,8(a0)
     df2:	0001                	nop
     df4:	0100                	addi	s0,sp,128
     df6:	0408                	addi	a0,sp,512
     df8:	0119                	addi	sp,sp,6
     dfa:	0000                	unimp
     dfc:	0e02                	c.slli64	t3
     dfe:	0000                	unimp
     e00:	0300                	addi	s0,sp,384
     e02:	007d0d43          	fmadd.s	fs10,fs10,ft7,ft0,rne
     e06:	0000                	unimp
     e08:	430d                	li	t1,3
     e0a:	0002                	c.slli64	zero
     e0c:	0500                	addi	s0,sp,640
     e0e:	0906                	slli	s2,s2,0x1
     e10:	8f04                	.insn	2, 0x8f04
     e12:	0001                	nop
     e14:	1300                	addi	s0,sp,416
     e16:	009e                	slli	ra,ra,0x7
     e18:	0000                	unimp
     e1a:	000000cb          	fnmsub.s	ft1,ft0,ft0,ft0,rne
     e1e:	0000cb03          	lbu	s6,0(ra) # 786 <main-0x11fff87a>
     e22:	0300                	addi	s0,sp,384
     e24:	0040                	addi	s0,sp,4
     e26:	0000                	unimp
     e28:	0e00                	addi	s0,sp,784
     e2a:	d808                	sw	a0,48(s0)
     e2c:	0000                	unimp
     e2e:	0100                	addi	s0,sp,128
     e30:	0801                	addi	a6,a6,0
     e32:	0114                	addi	a3,sp,128
     e34:	0000                	unimp
     e36:	0000d10f          	.insn	4, 0xd10f
     e3a:	0400                	addi	s0,sp,512
     e3c:	0190                	addi	a2,sp,192
     e3e:	0000                	unimp
     e40:	9e14                	.insn	2, 0x9e14
     e42:	0000                	unimp
     e44:	f200                	sd	s0,32(a2)
     e46:	0000                	unimp
     e48:	0300                	addi	s0,sp,384
     e4a:	000000cb          	fnmsub.s	ft1,ft0,ft0,ft0,rne
     e4e:	0005                	c.nop	1
     e50:	4d10                	lw	a2,24(a0)
     e52:	0002                	c.slli64	zero
     e54:	0100                	addi	s0,sp,128
     e56:	06220113          	addi	sp,tp,98 # 62 <main-0x11ffff9e>
     e5a:	1200                	addi	s0,sp,288
     e5c:	0000                	unimp
     e5e:	0000                	unimp
     e60:	000c                	.insn	2, 0x000c
     e62:	0000                	unimp
     e64:	0000                	unimp
     e66:	0000                	unimp
     e68:	9c01                	subw	s0,s0,s0
     e6a:	011e                	slli	sp,sp,0x7
     e6c:	0000                	unimp
     e6e:	2e06                	fld	ft8,64(sp)
     e70:	0006                	c.slli	zero,0x1
     e72:	0012                	c.slli	zero,0x4
     e74:	0000                	unimp
     e76:	aa00                	fsd	fs0,16(a2)
     e78:	0000                	unimp
     e7a:	0000                	unimp
     e7c:	e111                	bnez	a0,e80 <main-0x11fff180>
     e7e:	0001                	nop
     e80:	0100                	addi	s0,sp,128
     e82:	0109                	addi	sp,sp,2
     e84:	05e2                	slli	a1,a1,0x18
     e86:	1200                	addi	s0,sp,288
     e88:	0000                	unimp
     e8a:	0000                	unimp
     e8c:	0040                	addi	s0,sp,4
     e8e:	0000                	unimp
     e90:	0000                	unimp
     e92:	0000                	unimp
     e94:	9c01                	subw	s0,s0,s0
     e96:	6d12                	ld	s10,256(sp)
     e98:	01006773          	csrrsi	a4,0x10,0
     e9c:	1509                	addi	a0,a0,-30
     e9e:	000000cb          	fnmsub.s	ft1,ft0,ft0,ft0,rne
     ea2:	083a                	slli	a6,a6,0xe
     ea4:	0000                	unimp
     ea6:	0836                	slli	a6,a6,0xd
     ea8:	0000                	unimp
     eaa:	1305                	addi	t1,t1,-31
     eac:	7061                	c.lui	zero,0xffff8
     eae:	0100                	addi	s0,sp,128
     eb0:	0d0a                	slli	s10,s10,0x2
     eb2:	0040                	addi	s0,sp,4
     eb4:	0000                	unimp
     eb6:	7fa89103          	lh	sp,2042(a7)
     eba:	00060e07          	.insn	4, 0x00060e07
     ebe:	0012                	c.slli	zero,0x4
     ec0:	0000                	unimp
     ec2:	dd00                	sw	s0,56(a0)
     ec4:	0000                	unimp
     ec6:	7b00                	ld	s0,48(a4)
     ec8:	0001                	nop
     eca:	0800                	addi	s0,sp,16
     ecc:	5a01                	li	s4,-32
     ece:	0309                	addi	t1,t1,2
     ed0:	10b0                	addi	a2,sp,104
     ed2:	1200                	addi	s0,sp,288
     ed4:	0000                	unimp
     ed6:	0000                	unimp
     ed8:	0700                	addi	s0,sp,896
     eda:	061a                	slli	a2,a2,0x6
     edc:	1200                	addi	s0,sp,288
     ede:	0000                	unimp
     ee0:	0000                	unimp
     ee2:	00b2                	slli	ra,ra,0xc
     ee4:	0000                	unimp
     ee6:	00000193          	li	gp,0
     eea:	0108                	addi	a0,sp,128
     eec:	025a                	slli	tp,tp,0x16
     eee:	0078                	addi	a4,sp,12
     ef0:	0600                	addi	s0,sp,768
     ef2:	0622                	slli	a2,a2,0x8
     ef4:	1200                	addi	s0,sp,288
     ef6:	0000                	unimp
     ef8:	0000                	unimp
     efa:	00aa                	slli	ra,ra,0xa
     efc:	0000                	unimp
     efe:	0000                	unimp
     f00:	04ae                	slli	s1,s1,0xb
     f02:	0000                	unimp
     f04:	0005                	c.nop	1
     f06:	0801                	addi	a6,a6,0
     f08:	000005eb          	.insn	4, 0x05eb
     f0c:	00002b0b          	.insn	4, 0x2b0b
     f10:	1d00                	addi	s0,sp,688
     f12:	000001a7          	.insn	4, 0x01a7
     f16:	015e                	slli	sp,sp,0x17
     f18:	0000                	unimp
     f1a:	062e                	slli	a2,a2,0xb
     f1c:	1200                	addi	s0,sp,288
     f1e:	0000                	unimp
     f20:	0000                	unimp
     f22:	004a                	c.slli	zero,0x12
     f24:	0000                	unimp
     f26:	0000                	unimp
     f28:	0000                	unimp
     f2a:	00000fcb          	fnmsub.s	ft11,ft0,ft0,ft0,rne
     f2e:	0b080103          	lb	sp,176(a6)
     f32:	0001                	nop
     f34:	0300                	addi	s0,sp,384
     f36:	0601                	addi	a2,a2,0
     f38:	010d                	addi	sp,sp,3
     f3a:	0000                	unimp
     f3c:	2d070203          	lb	tp,720(a4)
     f40:	0001                	nop
     f42:	0300                	addi	s0,sp,384
     f44:	0502                	c.slli64	a0
     f46:	0000014b          	fnmsub.s	ft2,ft0,ft0,ft0,rne
     f4a:	1e070403          	lb	s0,480(a4)
     f4e:	0000                	unimp
     f50:	0c00                	addi	s0,sp,528
     f52:	0504                	addi	s1,sp,640
     f54:	6e69                	lui	t3,0x1a
     f56:	0074                	addi	a3,sp,12
     f58:	7509                	lui	a0,0xfffe2
     f5a:	3436                	fld	fs0,360(sp)
     f5c:	3d00                	fld	fs0,56(a0)
     f5e:	0062                	c.slli	zero,0x18
     f60:	0000                	unimp
     f62:	14070803          	lb	a6,320(a4)
     f66:	0000                	unimp
     f68:	0900                	addi	s0,sp,144
     f6a:	3669                	addiw	a2,a2,-6
     f6c:	0034                	addi	a3,sp,8
     f6e:	733e                	ld	t1,488(sp)
     f70:	0000                	unimp
     f72:	0300                	addi	s0,sp,384
     f74:	0508                	addi	a0,sp,640
     f76:	0000                	unimp
     f78:	0000                	unimp
     f7a:	45040403          	lb	s0,1104(s0)
     f7e:	0001                	nop
     f80:	0300                	addi	s0,sp,384
     f82:	0408                	addi	a0,sp,512
     f84:	0119                	addi	sp,sp,6
     f86:	0000                	unimp
     f88:	e908                	sd	a0,16(a0)
     f8a:	0001                	nop
     f8c:	4200                	lw	s0,0(a2)
     f8e:	580d                	li	a6,-29
     f90:	0000                	unimp
     f92:	0800                	addi	s0,sp,16
     f94:	000e                	c.slli	zero,0x3
     f96:	0000                	unimp
     f98:	00690d43          	fmadd.s	fs10,fs2,ft6,ft0,rne
     f9c:	0000                	unimp
     f9e:	5c08                	lw	a0,56(s0)
     fa0:	0002                	c.slli64	zero
     fa2:	4c00                	lw	s0,24(s0)
     fa4:	0000880f          	.insn	4, 0x880f
     fa8:	0d00                	addi	s0,sp,656
     faa:	027c                	addi	a5,sp,268
     fac:	0000                	unimp
     fae:	1101                	addi	sp,sp,-32
     fb0:	9e01                	subw	a2,a2,s0
     fb2:	0000                	unimp
     fb4:	5600                	lw	s0,40(a2)
     fb6:	0006                	c.slli	zero,0x1
     fb8:	0012                	c.slli	zero,0x4
     fba:	0000                	unimp
     fbc:	2200                	fld	fs0,0(a2)
     fbe:	0000                	unimp
     fc0:	0000                	unimp
     fc2:	0000                	unimp
     fc4:	0100                	addi	s0,sp,128
     fc6:	9e9c                	.insn	2, 0x9e9c
     fc8:	0001                	nop
     fca:	0e00                	addi	s0,sp,784
     fcc:	0271                	addi	tp,tp,28 # 1c <main-0x11ffffe4>
     fce:	0000                	unimp
     fd0:	1201                	addi	tp,tp,-32 # ffffffffffffffe0 <__sheap+0xffffffffedffcfe0>
     fd2:	9e12                	add	t3,t3,tp
     fd4:	0000                	unimp
     fd6:	0900                	addi	s0,sp,144
     fd8:	00211003          	lh	zero,2(sp)
     fdc:	0012                	c.slli	zero,0x4
     fde:	0000                	unimp
     fe0:	0400                	addi	s0,sp,512
     fe2:	00000403          	lb	s0,0(zero) # 0 <main-0x12000000>
     fe6:	0660                	addi	s0,sp,780
     fe8:	1200                	addi	s0,sp,288
     fea:	0000                	unimp
     fec:	0000                	unimp
     fee:	6006                	.insn	2, 0x6006
     ff0:	0006                	c.slli	zero,0x1
     ff2:	0012                	c.slli	zero,0x4
     ff4:	0000                	unimp
     ff6:	0e00                	addi	s0,sp,784
     ff8:	0000                	unimp
     ffa:	0000                	unimp
     ffc:	0000                	unimp
     ffe:	0100                	addi	s0,sp,128
    1000:	1914                	addi	a3,sp,176
    1002:	2b04                	fld	fs1,16(a4)
    1004:	0004                	.insn	2, 0x0004
    1006:	6000                	ld	s0,0(s0)
    1008:	0006                	c.slli	zero,0x1
    100a:	0012                	c.slli	zero,0x4
    100c:	0000                	unimp
    100e:	0800                	addi	s0,sp,16
    1010:	0660                	addi	s0,sp,780
    1012:	1200                	addi	s0,sp,288
    1014:	0000                	unimp
    1016:	0000                	unimp
    1018:	000e                	c.slli	zero,0x3
    101a:	0000                	unimp
    101c:	0000                	unimp
    101e:	0000                	unimp
    1020:	1502                	slli	a0,a0,0x20
    1022:	04380213          	addi	tp,a6,67
    1026:	0000                	unimp
    1028:	00000853          	fadd.s	fa6,ft0,ft0,rne
    102c:	0851                	addi	a6,a6,20
    102e:	0000                	unimp
    1030:	4302                	lw	t1,0(sp)
    1032:	0004                	.insn	2, 0x0004
    1034:	5c00                	lw	s0,56(s0)
    1036:	0008                	.insn	2, 0x0008
    1038:	5a00                	lw	s0,48(a2)
    103a:	0008                	.insn	2, 0x0008
    103c:	0200                	addi	s0,sp,256
    103e:	044e                	slli	s0,s0,0x13
    1040:	0000                	unimp
    1042:	085c                	addi	a5,sp,20
    1044:	0000                	unimp
    1046:	085a                	slli	a6,a6,0x16
    1048:	0000                	unimp
    104a:	5902                	lw	s2,32(sp)
    104c:	0004                	.insn	2, 0x0004
    104e:	5c00                	lw	s0,56(s0)
    1050:	0008                	.insn	2, 0x0008
    1052:	5a00                	lw	s0,48(a2)
    1054:	0008                	.insn	2, 0x0008
    1056:	0200                	addi	s0,sp,256
    1058:	0464                	addi	s1,sp,524
    105a:	0000                	unimp
    105c:	085c                	addi	a5,sp,20
    105e:	0000                	unimp
    1060:	085a                	slli	a6,a6,0x16
    1062:	0000                	unimp
    1064:	6f02                	ld	t5,0(sp)
    1066:	0004                	.insn	2, 0x0004
    1068:	5c00                	lw	s0,56(s0)
    106a:	0008                	.insn	2, 0x0008
    106c:	5a00                	lw	s0,48(a2)
    106e:	0008                	.insn	2, 0x0008
    1070:	0100                	addi	s0,sp,128
    1072:	047a                	slli	s0,s0,0x1e
    1074:	0000                	unimp
    1076:	5a01                	li	s4,-32
    1078:	8301                	c.srli64	a4
    107a:	0004                	.insn	2, 0x0004
    107c:	0100                	addi	s0,sp,128
    107e:	048c015b          	.insn	4, 0x048c015b
    1082:	0000                	unimp
    1084:	5c01                	li	s8,-32
    1086:	9501                	srai	a0,a0,0x20
    1088:	0004                	.insn	2, 0x0004
    108a:	0100                	addi	s0,sp,128
    108c:	015d                	addi	sp,sp,23
    108e:	049e                	slli	s1,s1,0x7
    1090:	0000                	unimp
    1092:	5e01                	li	t3,-32
    1094:	a701                	j	1794 <main-0x11ffe86c>
    1096:	0004                	.insn	2, 0x0004
    1098:	0100                	addi	s0,sp,128
    109a:	0061                	c.nop	24
    109c:	0000                	unimp
    109e:	0002660f          	.insn	4, 0x0002660f
    10a2:	0100                	addi	s0,sp,128
    10a4:	010c                	addi	a1,sp,128
    10a6:	0644                	addi	s1,sp,772
    10a8:	1200                	addi	s0,sp,288
    10aa:	0000                	unimp
    10ac:	0000                	unimp
    10ae:	0012                	c.slli	zero,0x4
    10b0:	0000                	unimp
    10b2:	0000                	unimp
    10b4:	0000                	unimp
    10b6:	9c01                	subw	s0,s0,s0
    10b8:	0279                	addi	tp,tp,30 # 1e <main-0x11ffffe2>
    10ba:	0000                	unimp
    10bc:	f904                	sd	s1,48(a0)
    10be:	44000003          	lb	zero,1088(zero) # 440 <main-0x11fffbc0>
    10c2:	0006                	c.slli	zero,0x1
    10c4:	0012                	c.slli	zero,0x4
    10c6:	0000                	unimp
    10c8:	0200                	addi	s0,sp,256
    10ca:	0644                	addi	s1,sp,772
    10cc:	1200                	addi	s0,sp,288
    10ce:	0000                	unimp
    10d0:	0000                	unimp
    10d2:	0010                	.insn	2, 0x0010
    10d4:	0000                	unimp
    10d6:	0000                	unimp
    10d8:	0000                	unimp
    10da:	0d01                	addi	s10,s10,0
    10dc:	0405                	addi	s0,s0,1
    10de:	0000042b          	.insn	4, 0x042b
    10e2:	0644                	addi	s1,sp,772
    10e4:	1200                	addi	s0,sp,288
    10e6:	0000                	unimp
    10e8:	0000                	unimp
    10ea:	4404                	lw	s1,8(s0)
    10ec:	0006                	c.slli	zero,0x1
    10ee:	0012                	c.slli	zero,0x4
    10f0:	0000                	unimp
    10f2:	1000                	addi	s0,sp,32
    10f4:	0000                	unimp
    10f6:	0000                	unimp
    10f8:	0000                	unimp
    10fa:	0200                	addi	s0,sp,256
    10fc:	0c6d                	addi	s8,s8,27
    10fe:	3802                	fld	fa6,32(sp)
    1100:	0004                	.insn	2, 0x0004
    1102:	6500                	ld	s0,8(a0)
    1104:	0008                	.insn	2, 0x0008
    1106:	6300                	ld	s0,0(a4)
    1108:	0008                	.insn	2, 0x0008
    110a:	0200                	addi	s0,sp,256
    110c:	00000443          	fmadd.s	fs0,ft0,ft0,ft0,rne
    1110:	086e                	slli	a6,a6,0x1b
    1112:	0000                	unimp
    1114:	086c                	addi	a1,sp,28
    1116:	0000                	unimp
    1118:	4e02                	lw	t3,0(sp)
    111a:	0004                	.insn	2, 0x0004
    111c:	6e00                	ld	s0,24(a2)
    111e:	0008                	.insn	2, 0x0008
    1120:	6c00                	ld	s0,24(s0)
    1122:	0008                	.insn	2, 0x0008
    1124:	0200                	addi	s0,sp,256
    1126:	0459                	addi	s0,s0,22
    1128:	0000                	unimp
    112a:	086e                	slli	a6,a6,0x1b
    112c:	0000                	unimp
    112e:	086c                	addi	a1,sp,28
    1130:	0000                	unimp
    1132:	6402                	ld	s0,0(sp)
    1134:	0004                	.insn	2, 0x0004
    1136:	6e00                	ld	s0,24(a2)
    1138:	0008                	.insn	2, 0x0008
    113a:	6c00                	ld	s0,24(s0)
    113c:	0008                	.insn	2, 0x0008
    113e:	0200                	addi	s0,sp,256
    1140:	0000046f          	jal	s0,1140 <main-0x11ffeec0>
    1144:	086e                	slli	a6,a6,0x1b
    1146:	0000                	unimp
    1148:	086c                	addi	a1,sp,28
    114a:	0000                	unimp
    114c:	7a01                	lui	s4,0xfffe0
    114e:	0004                	.insn	2, 0x0004
    1150:	0100                	addi	s0,sp,128
    1152:	015a                	slli	sp,sp,0x16
    1154:	00000483          	lb	s1,0(zero) # 0 <main-0x12000000>
    1158:	5b01                	li	s6,-32
    115a:	8c01                	sub	s0,s0,s0
    115c:	0004                	.insn	2, 0x0004
    115e:	0100                	addi	s0,sp,128
    1160:	015c                	addi	a5,sp,132
    1162:	0495                	addi	s1,s1,5
    1164:	0000                	unimp
    1166:	5d01                	li	s10,-32
    1168:	9e01                	subw	a2,a2,s0
    116a:	0004                	.insn	2, 0x0004
    116c:	0100                	addi	s0,sp,128
    116e:	015e                	slli	sp,sp,0x17
    1170:	000004a7          	.insn	4, 0x04a7
    1174:	6101                	addi	sp,sp,0
    1176:	0000                	unimp
    1178:	1000                	addi	s0,sp,32
    117a:	00000243          	fmadd.s	ft4,ft0,ft0,ft0,rne
    117e:	0601                	addi	a2,a2,0
    1180:	2e01                	sext.w	t3,t3
    1182:	0006                	c.slli	zero,0x1
    1184:	0012                	c.slli	zero,0x4
    1186:	0000                	unimp
    1188:	1600                	addi	s0,sp,800
    118a:	0000                	unimp
    118c:	0000                	unimp
    118e:	0000                	unimp
    1190:	0100                	addi	s0,sp,128
    1192:	f99c                	sd	a5,48(a1)
    1194:	11000003          	lb	zero,272(zero) # 110 <main-0x11fffef0>
    1198:	00000403          	lb	s0,0(zero) # 0 <main-0x12000000>
    119c:	062e                	slli	a2,a2,0xb
    119e:	1200                	addi	s0,sp,288
    11a0:	0000                	unimp
    11a2:	0000                	unimp
    11a4:	2e02                	fld	ft8,0(sp)
    11a6:	0006                	c.slli	zero,0x1
    11a8:	0012                	c.slli	zero,0x4
    11aa:	0000                	unimp
    11ac:	1000                	addi	s0,sp,32
    11ae:	0000                	unimp
    11b0:	0000                	unimp
    11b2:	0000                	unimp
    11b4:	0100                	addi	s0,sp,128
    11b6:	03571307          	.insn	4, 0x03571307
    11ba:	0000                	unimp
    11bc:	2b04                	fld	fs1,16(a4)
    11be:	0004                	.insn	2, 0x0004
    11c0:	2e00                	fld	fs0,24(a2)
    11c2:	0006                	c.slli	zero,0x1
    11c4:	0012                	c.slli	zero,0x4
    11c6:	0000                	unimp
    11c8:	0400                	addi	s0,sp,512
    11ca:	062e                	slli	a2,a2,0xb
    11cc:	1200                	addi	s0,sp,288
    11ce:	0000                	unimp
    11d0:	0000                	unimp
    11d2:	0010                	.insn	2, 0x0010
    11d4:	0000                	unimp
    11d6:	0000                	unimp
    11d8:	0000                	unimp
    11da:	1502                	slli	a0,a0,0x20
    11dc:	04380213          	addi	tp,a6,67
    11e0:	0000                	unimp
    11e2:	00000877          	.insn	4, 0x0877
    11e6:	0875                	addi	a6,a6,29
    11e8:	0000                	unimp
    11ea:	4302                	lw	t1,0(sp)
    11ec:	0004                	.insn	2, 0x0004
    11ee:	8000                	.insn	2, 0x8000
    11f0:	0008                	.insn	2, 0x0008
    11f2:	7e00                	ld	s0,56(a2)
    11f4:	0008                	.insn	2, 0x0008
    11f6:	0200                	addi	s0,sp,256
    11f8:	044e                	slli	s0,s0,0x13
    11fa:	0000                	unimp
    11fc:	0880                	addi	s0,sp,80
    11fe:	0000                	unimp
    1200:	087e                	slli	a6,a6,0x1f
    1202:	0000                	unimp
    1204:	5902                	lw	s2,32(sp)
    1206:	0004                	.insn	2, 0x0004
    1208:	8000                	.insn	2, 0x8000
    120a:	0008                	.insn	2, 0x0008
    120c:	7e00                	ld	s0,56(a2)
    120e:	0008                	.insn	2, 0x0008
    1210:	0200                	addi	s0,sp,256
    1212:	0464                	addi	s1,sp,524
    1214:	0000                	unimp
    1216:	0880                	addi	s0,sp,80
    1218:	0000                	unimp
    121a:	087e                	slli	a6,a6,0x1f
    121c:	0000                	unimp
    121e:	6f02                	ld	t5,0(sp)
    1220:	0004                	.insn	2, 0x0004
    1222:	8000                	.insn	2, 0x8000
    1224:	0008                	.insn	2, 0x0008
    1226:	7e00                	ld	s0,56(a2)
    1228:	0008                	.insn	2, 0x0008
    122a:	0100                	addi	s0,sp,128
    122c:	047a                	slli	s0,s0,0x1e
    122e:	0000                	unimp
    1230:	5a01                	li	s4,-32
    1232:	8301                	c.srli64	a4
    1234:	0004                	.insn	2, 0x0004
    1236:	0100                	addi	s0,sp,128
    1238:	048c015b          	.insn	4, 0x048c015b
    123c:	0000                	unimp
    123e:	5c01                	li	s8,-32
    1240:	9501                	srai	a0,a0,0x20
    1242:	0004                	.insn	2, 0x0004
    1244:	0100                	addi	s0,sp,128
    1246:	015d                	addi	sp,sp,23
    1248:	049e                	slli	s1,s1,0x7
    124a:	0000                	unimp
    124c:	5e01                	li	t3,-32
    124e:	a701                	j	194e <main-0x11ffe6b2>
    1250:	0004                	.insn	2, 0x0004
    1252:	0100                	addi	s0,sp,128
    1254:	0061                	c.nop	24
    1256:	0400                	addi	s0,sp,512
    1258:	040d                	addi	s0,s0,3
    125a:	0000                	unimp
    125c:	063e                	slli	a2,a2,0xf
    125e:	1200                	addi	s0,sp,288
    1260:	0000                	unimp
    1262:	0000                	unimp
    1264:	3e14                	fld	fa3,56(a2)
    1266:	0006                	c.slli	zero,0x1
    1268:	0012                	c.slli	zero,0x4
    126a:	0000                	unimp
    126c:	0600                	addi	s0,sp,768
    126e:	0000                	unimp
    1270:	0000                	unimp
    1272:	0000                	unimp
    1274:	0100                	addi	s0,sp,128
    1276:	1e020507          	.insn	4, 0x1e020507
    127a:	0004                	.insn	2, 0x0004
    127c:	8900                	.insn	2, 0x8900
    127e:	0008                	.insn	2, 0x0008
    1280:	8700                	.insn	2, 0x8700
    1282:	0008                	.insn	2, 0x0008
    1284:	0400                	addi	s0,sp,512
    1286:	0000042b          	.insn	4, 0x042b
    128a:	063e                	slli	a2,a2,0xf
    128c:	1200                	addi	s0,sp,288
    128e:	0000                	unimp
    1290:	0000                	unimp
    1292:	3e16                	fld	ft8,352(sp)
    1294:	0006                	c.slli	zero,0x1
    1296:	0012                	c.slli	zero,0x4
    1298:	0000                	unimp
    129a:	0600                	addi	s0,sp,768
    129c:	0000                	unimp
    129e:	0000                	unimp
    12a0:	0000                	unimp
    12a2:	0200                	addi	s0,sp,256
    12a4:	1309                	addi	t1,t1,-30
    12a6:	00043807          	fld	fa6,0(s0)
    12aa:	0200                	addi	s0,sp,256
    12ac:	00000443          	fmadd.s	fs0,ft0,ft0,ft0,rne
    12b0:	0891                	addi	a7,a7,4
    12b2:	0000                	unimp
    12b4:	0000088f          	.insn	4, 0x088f
    12b8:	00044e07          	.insn	4, 0x00044e07
    12bc:	0700                	addi	s0,sp,896
    12be:	0459                	addi	s0,s0,22
    12c0:	0000                	unimp
    12c2:	00046407          	.insn	4, 0x00046407
    12c6:	0700                	addi	s0,sp,896
    12c8:	0000046f          	jal	s0,12c8 <main-0x11ffed38>
    12cc:	7a01                	lui	s4,0xfffe0
    12ce:	0004                	.insn	2, 0x0004
    12d0:	0100                	addi	s0,sp,128
    12d2:	015a                	slli	sp,sp,0x16
    12d4:	00000483          	lb	s1,0(zero) # 0 <main-0x12000000>
    12d8:	5b01                	li	s6,-32
    12da:	8c01                	sub	s0,s0,s0
    12dc:	0004                	.insn	2, 0x0004
    12de:	0100                	addi	s0,sp,128
    12e0:	015c                	addi	a5,sp,132
    12e2:	0495                	addi	s1,s1,5
    12e4:	0000                	unimp
    12e6:	5d01                	li	s10,-32
    12e8:	9e01                	subw	a2,a2,s0
    12ea:	0004                	.insn	2, 0x0004
    12ec:	0100                	addi	s0,sp,128
    12ee:	015e                	slli	sp,sp,0x17
    12f0:	000004a7          	.insn	4, 0x04a7
    12f4:	6101                	addi	sp,sp,0
    12f6:	0000                	unimp
    12f8:	0a00                	addi	s0,sp,272
    12fa:	0262                	slli	tp,tp,0x18
    12fc:	0000                	unimp
    12fe:	936c                	.insn	2, 0x936c
    1300:	0000                	unimp
    1302:	0a00                	addi	s0,sp,272
    1304:	0278                	addi	a4,sp,268
    1306:	0000                	unimp
    1308:	9314                	.insn	2, 0x9314
    130a:	0000                	unimp
    130c:	1200                	addi	s0,sp,288
    130e:	0288                	addi	a0,sp,320
    1310:	0000                	unimp
    1312:	0802                	c.slli64	a6
    1314:	9301                	srli	a4,a4,0x20
    1316:	0000                	unimp
    1318:	0300                	addi	s0,sp,384
    131a:	0000042b          	.insn	4, 0x042b
    131e:	64697413          	andi	s0,s2,1606
    1322:	0200                	addi	s0,sp,256
    1324:	1508                	addi	a0,sp,672
    1326:	009e                	slli	ra,ra,0x7
    1328:	0000                	unimp
    132a:	1400                	addi	s0,sp,544
    132c:	0222                	slli	tp,tp,0x8
    132e:	0000                	unimp
    1330:	58010503          	lb	a0,1408(sp)
    1334:	0000                	unimp
    1336:	0300                	addi	s0,sp,384
    1338:	0d05                	addi	s10,s10,1
    133a:	0002                	c.slli64	zero
    133c:	0600                	addi	s0,sp,768
    133e:	0000880b          	.insn	4, 0x880b
    1342:	0500                	addi	s0,sp,640
    1344:	00000203          	lb	tp,0(zero) # 0 <main-0x12000000>
    1348:	00580907          	.insn	4, 0x00580907
    134c:	0000                	unimp
    134e:	1305                	addi	t1,t1,-31
    1350:	0002                	c.slli64	zero
    1352:	0800                	addi	s0,sp,16
    1354:	5809                	li	a6,-30
    1356:	0000                	unimp
    1358:	0500                	addi	s0,sp,640
    135a:	0218                	addi	a4,sp,256
    135c:	0000                	unimp
    135e:	0909                	addi	s2,s2,2
    1360:	0058                	addi	a4,sp,4
    1362:	0000                	unimp
    1364:	0805                	addi	a6,a6,1
    1366:	0002                	c.slli64	zero
    1368:	0a00                	addi	s0,sp,272
    136a:	5809                	li	a6,-30
    136c:	0000                	unimp
    136e:	0500                	addi	s0,sp,640
    1370:	021d                	addi	tp,tp,7 # 7 <main-0x11fffff9>
    1372:	0000                	unimp
    1374:	0058090b          	.insn	4, 0x0058090b
    1378:	0000                	unimp
    137a:	6106                	ld	sp,64(sp)
    137c:	0030                	addi	a2,sp,8
    137e:	580d                	li	a6,-29
    1380:	0000                	unimp
    1382:	0600                	addi	s0,sp,768
    1384:	3161                	addiw	sp,sp,-8
    1386:	0e00                	addi	s0,sp,784
    1388:	0058                	addi	a4,sp,4
    138a:	0000                	unimp
    138c:	6106                	ld	sp,64(sp)
    138e:	0032                	c.slli	zero,0xc
    1390:	0000580f          	.insn	4, 0x580f
    1394:	0600                	addi	s0,sp,768
    1396:	3361                	addiw	t1,t1,-8
    1398:	1000                	addi	s0,sp,32
    139a:	0058                	addi	a4,sp,4
    139c:	0000                	unimp
    139e:	6106                	ld	sp,64(sp)
    13a0:	0034                	addi	a3,sp,8
    13a2:	5811                	li	a6,-28
    13a4:	0000                	unimp
    13a6:	0600                	addi	s0,sp,768
    13a8:	3761                	addiw	a4,a4,-8
    13aa:	1200                	addi	s0,sp,288
    13ac:	0058                	addi	a4,sp,4
    13ae:	0000                	unimp
    13b0:	0000                	unimp
    13b2:	0101                	addi	sp,sp,0
    13b4:	0000                	unimp
    13b6:	0005                	c.nop	1
    13b8:	0801                	addi	a6,a6,0
    13ba:	0758                	addi	a4,sp,900
    13bc:	0000                	unimp
    13be:	2b05                	addiw	s6,s6,1
    13c0:	0000                	unimp
    13c2:	1d00                	addi	s0,sp,688
    13c4:	01ae                	slli	gp,gp,0xb
    13c6:	0000                	unimp
    13c8:	015e                	slli	sp,sp,0x17
    13ca:	0000                	unimp
    13cc:	0678                	addi	a4,sp,780
    13ce:	1200                	addi	s0,sp,288
    13d0:	0000                	unimp
    13d2:	0000                	unimp
    13d4:	0018                	.insn	2, 0x0018
    13d6:	0000                	unimp
    13d8:	0000                	unimp
    13da:	0000                	unimp
    13dc:	127e                	slli	tp,tp,0x3f
    13de:	0000                	unimp
    13e0:	0101                	addi	sp,sp,0
    13e2:	0b08                	addi	a0,sp,400
    13e4:	0001                	nop
    13e6:	0100                	addi	s0,sp,128
    13e8:	0601                	addi	a2,a2,0
    13ea:	010d                	addi	sp,sp,3
    13ec:	0000                	unimp
    13ee:	0201                	addi	tp,tp,0 # 0 <main-0x12000000>
    13f0:	00012d07          	flw	fs10,0(sp)
    13f4:	0100                	addi	s0,sp,128
    13f6:	0502                	c.slli64	a0
    13f8:	0000014b          	fnmsub.s	ft2,ft0,ft0,ft0,rne
    13fc:	0401                	addi	s0,s0,0
    13fe:	00001e07          	.insn	4, 0x1e07
    1402:	0600                	addi	s0,sp,768
    1404:	0504                	addi	s1,sp,640
    1406:	6e69                	lui	t3,0x1a
    1408:	0074                	addi	a3,sp,12
    140a:	0801                	addi	a6,a6,0
    140c:	00001407          	.insn	4, 0x1407
    1410:	0700                	addi	s0,sp,896
    1412:	3669                	addiw	a2,a2,-6
    1414:	0034                	addi	a3,sp,8
    1416:	3e02                	fld	ft8,32(sp)
    1418:	6b1d                	lui	s6,0x7
    141a:	0000                	unimp
    141c:	0100                	addi	s0,sp,128
    141e:	0508                	addi	a0,sp,640
    1420:	0000                	unimp
    1422:	0000                	unimp
    1424:	0401                	addi	s0,s0,0
    1426:	4504                	lw	s1,8(a0)
    1428:	0001                	nop
    142a:	0100                	addi	s0,sp,128
    142c:	0408                	addi	a0,sp,512
    142e:	0119                	addi	sp,sp,6
    1430:	0000                	unimp
    1432:	0e08                	addi	a0,sp,784
    1434:	0000                	unimp
    1436:	0200                	addi	s0,sp,256
    1438:	005f0d43          	fmadd.s	fs10,ft10,ft5,ft0,rne
    143c:	0000                	unimp
    143e:	4309                	li	t1,2
    1440:	0002                	c.slli64	zero
    1442:	0300                	addi	s0,sp,384
    1444:	0906                	slli	s2,s2,0x1
    1446:	960a                	add	a2,a2,sp
    1448:	0002                	c.slli64	zero
    144a:	0100                	addi	s0,sp,128
    144c:	00800e07          	.insn	4, 0x00800e07
    1450:	0000                	unimp
    1452:	000000af          	.insn	4, 0x00af
    1456:	8002                	.insn	2, 0x8002
    1458:	0000                	unimp
    145a:	0200                	addi	s0,sp,256
    145c:	000000af          	.insn	4, 0x00af
    1460:	0300                	addi	s0,sp,384
    1462:	00b4                	addi	a3,sp,72
    1464:	0000                	unimp
    1466:	0000b903          	ld	s2,0(ra)
    146a:	0100                	addi	s0,sp,128
    146c:	0801                	addi	a6,a6,0
    146e:	0114                	addi	a3,sp,128
    1470:	0000                	unimp
    1472:	00029d0b          	.insn	4, 0x00029d0b
    1476:	0100                	addi	s0,sp,128
    1478:	010a                	slli	sp,sp,0x2
    147a:	0678                	addi	a4,sp,780
    147c:	1200                	addi	s0,sp,288
    147e:	0000                	unimp
    1480:	0000                	unimp
    1482:	0018                	.insn	2, 0x0018
    1484:	0000                	unimp
    1486:	0000                	unimp
    1488:	0000                	unimp
    148a:	9c01                	subw	s0,s0,s0
    148c:	880c                	.insn	2, 0x880c
    148e:	0006                	c.slli	zero,0x1
    1490:	0012                	c.slli	zero,0x4
    1492:	0000                	unimp
    1494:	9400                	.insn	2, 0x9400
    1496:	0000                	unimp
    1498:	f600                	sd	s0,40(a2)
    149a:	0000                	unimp
    149c:	0400                	addi	s0,sp,512
    149e:	5a01                	li	s4,-32
    14a0:	3001                	.insn	2, 0x3001
    14a2:	0104                	addi	s1,sp,128
    14a4:	0030015b          	.insn	4, 0x0030015b
    14a8:	900d                	srli	s0,s0,0x23
    14aa:	0006                	c.slli	zero,0x1
    14ac:	0012                	c.slli	zero,0x4
    14ae:	0000                	unimp
    14b0:	8c00                	.insn	2, 0x8c00
    14b2:	0000                	unimp
    14b4:	0000                	unimp
    14b6:	2400                	fld	fs0,8(s0)
    14b8:	0000                	unimp
    14ba:	0500                	addi	s0,sp,640
    14bc:	0100                	addi	s0,sp,128
    14be:	1408                	addi	a0,sp,544
    14c0:	0008                	.insn	2, 0x0008
    14c2:	0100                	addi	s0,sp,128
    14c4:	1308                	addi	a0,sp,416
    14c6:	0000                	unimp
    14c8:	0690                	addi	a2,sp,832
    14ca:	1200                	addi	s0,sp,288
    14cc:	0000                	unimp
    14ce:	0000                	unimp
    14d0:	a218                	fsd	fa4,0(a2)
    14d2:	0002                	c.slli64	zero
    14d4:	a900                	fsd	fs0,16(a0)
    14d6:	0002                	c.slli64	zero
    14d8:	d200                	sw	s0,32(a2)
    14da:	0002                	c.slli64	zero
    14dc:	0100                	addi	s0,sp,128
    14de:	cd80                	sw	s0,24(a1)
    14e0:	05000003          	lb	zero,80(zero) # 50 <main-0x11ffffb0>
    14e4:	0100                	addi	s0,sp,128
    14e6:	2808                	fld	fa0,16(s0)
    14e8:	0008                	.insn	2, 0x0008
    14ea:	0b00                	addi	s0,sp,400
    14ec:	0000002b          	.insn	4, 0x002b
    14f0:	bc1d                	j	f26 <main-0x11fff0da>
    14f2:	0001                	nop
    14f4:	3c00                	fld	fs0,56(s0)
    14f6:	0001                	nop
    14f8:	6200                	ld	s0,0(a2)
    14fa:	0001                	nop
	...
    1504:	8000                	.insn	2, 0x8000
    1506:	07000013          	li	zero,112
    150a:	3875                	addiw	a6,a6,-3
    150c:	3700                	fld	fs0,40(a4)
    150e:	0038                	addi	a4,sp,8
    1510:	0000                	unimp
    1512:	2a09                	addiw	s4,s4,2 # fffffffffffe0002 <__sheap+0xffffffffedfdd002>
    1514:	0000                	unimp
    1516:	0300                	addi	s0,sp,384
    1518:	0801                	addi	a6,a6,0
    151a:	0000010b          	.insn	4, 0x010b
    151e:	0d060103          	lb	sp,208(a2)
    1522:	0001                	nop
    1524:	0300                	addi	s0,sp,384
    1526:	0702                	c.slli64	a4
    1528:	012d                	addi	sp,sp,11
    152a:	0000                	unimp
    152c:	4b050203          	lb	tp,1200(a0) # fffffffffffe24b0 <__sheap+0xffffffffedfdf4b0>
    1530:	0001                	nop
    1532:	0300                	addi	s0,sp,384
    1534:	0704                	addi	s1,sp,896
    1536:	001e                	c.slli	zero,0x7
    1538:	0000                	unimp
    153a:	040c                	addi	a1,sp,512
    153c:	6905                	lui	s2,0x1
    153e:	746e                	ld	s0,248(sp)
    1540:	0700                	addi	s0,sp,896
    1542:	3675                	addiw	a2,a2,-3
    1544:	0034                	addi	a3,sp,8
    1546:	6c3d                	lui	s8,0xf
    1548:	0000                	unimp
    154a:	0300                	addi	s0,sp,384
    154c:	0708                	addi	a0,sp,896
    154e:	0014                	.insn	2, 0x0014
    1550:	0000                	unimp
    1552:	34366907          	.insn	4, 0x34366907
    1556:	3e00                	fld	fs0,56(a2)
    1558:	007d                	c.nop	31
    155a:	0000                	unimp
    155c:	00050803          	lb	a6,0(a0)
    1560:	0000                	unimp
    1562:	0300                	addi	s0,sp,384
    1564:	0404                	addi	s1,sp,512
    1566:	0145                	addi	sp,sp,17
    1568:	0000                	unimp
    156a:	19040803          	lb	a6,400(s0)
    156e:	0001                	nop
    1570:	0a00                	addi	s0,sp,272
    1572:	01e9                	addi	gp,gp,26
    1574:	0000                	unimp
    1576:	6242                	ld	tp,16(sp)
    1578:	0000                	unimp
    157a:	0a00                	addi	s0,sp,272
    157c:	000e                	c.slli	zero,0x3
    157e:	0000                	unimp
    1580:	00007343          	fmadd.s	ft6,ft0,ft0,ft0
    1584:	0400                	addi	s0,sp,512
    1586:	00000307          	.insn	4, 0x0307
    158a:	9c50                	.insn	2, 0x9c50
    158c:	0000                	unimp
    158e:	8600                	.insn	2, 0x8600
    1590:	00120007          	.insn	4, 0x00120007
    1594:	0000                	unimp
    1596:	3400                	fld	fs0,40(s0)
    1598:	0000                	unimp
    159a:	0000                	unimp
    159c:	0000                	unimp
    159e:	0100                	addi	s0,sp,128
    15a0:	eb9c                	sd	a5,16(a5)
    15a2:	0000                	unimp
    15a4:	0100                	addi	s0,sp,128
    15a6:	50003173          	csrrc	sp,0x500,zero
    15aa:	eb14                	sd	a3,16(a4)
    15ac:	0000                	unimp
    15ae:	ad00                	fsd	fs0,24(a0)
    15b0:	0008                	.insn	2, 0x0008
    15b2:	a300                	fsd	fs0,0(a4)
    15b4:	0008                	.insn	2, 0x0008
    15b6:	0100                	addi	s0,sp,128
    15b8:	50003273          	csrrc	tp,0x500,zero
    15bc:	eb24                	sd	s1,80(a4)
    15be:	0000                	unimp
    15c0:	df00                	sw	s0,56(a4)
    15c2:	0008                	.insn	2, 0x0008
    15c4:	d300                	sw	s0,32(a4)
    15c6:	0008                	.insn	2, 0x0008
    15c8:	0000                	unimp
    15ca:	f705                	bnez	a4,14f2 <main-0x11ffeb0e>
    15cc:	0000                	unimp
    15ce:	0300                	addi	s0,sp,384
    15d0:	0801                	addi	a6,a6,0
    15d2:	0114                	addi	a3,sp,128
    15d4:	0000                	unimp
    15d6:	f009                	bnez	s0,14d8 <main-0x11ffeb28>
    15d8:	0000                	unimp
    15da:	0400                	addi	s0,sp,512
    15dc:	02ec                	addi	a1,sp,332
    15de:	0000                	unimp
    15e0:	4e46                	lw	t3,80(sp)
    15e2:	0001                	nop
    15e4:	5400                	lw	s0,40(s0)
    15e6:	00120007          	.insn	4, 0x00120007
    15ea:	0000                	unimp
    15ec:	3200                	fld	fs0,32(a2)
    15ee:	0000                	unimp
    15f0:	0000                	unimp
    15f2:	0000                	unimp
    15f4:	0100                	addi	s0,sp,128
    15f6:	4e9c                	lw	a5,24(a3)
    15f8:	0001                	nop
    15fa:	0600                	addi	s0,sp,768
    15fc:	0302                	c.slli64	t1
    15fe:	0000                	unimp
    1600:	0e46                	slli	t3,t3,0x11
    1602:	014e                	slli	sp,sp,0x13
    1604:	0000                	unimp
    1606:	5a01                	li	s4,-32
    1608:	7301                	lui	t1,0xfffe0
    160a:	6372                	ld	t1,280(sp)
    160c:	4600                	lw	s0,8(a2)
    160e:	eb20                	sd	s0,80(a4)
    1610:	0000                	unimp
    1612:	1300                	addi	s0,sp,416
    1614:	0009                	c.nop	2
    1616:	0d00                	addi	s0,sp,656
    1618:	0009                	c.nop	2
    161a:	0200                	addi	s0,sp,256
    161c:	0064                	addi	s1,sp,12
    161e:	014e0b47          	fmsub.s	fs6,ft8,fs4,ft0,rne
    1622:	0000                	unimp
    1624:	0934                	addi	a3,sp,152
    1626:	0000                	unimp
    1628:	092c                	addi	a1,sp,152
    162a:	0000                	unimp
    162c:	0500                	addi	s0,sp,640
    162e:	00f0                	addi	a2,sp,76
    1630:	0000                	unimp
    1632:	f304                	sd	s1,32(a4)
    1634:	0002                	c.slli64	zero
    1636:	3900                	fld	fs0,48(a0)
    1638:	014e                	slli	sp,sp,0x13
    163a:	0000                	unimp
    163c:	0722                	slli	a4,a4,0x8
    163e:	1200                	addi	s0,sp,288
    1640:	0000                	unimp
    1642:	0000                	unimp
    1644:	0032                	c.slli	zero,0xc
    1646:	0000                	unimp
    1648:	0000                	unimp
    164a:	0000                	unimp
    164c:	9c01                	subw	s0,s0,s0
    164e:	01c1                	addi	gp,gp,16
    1650:	0000                	unimp
    1652:	0206                	slli	tp,tp,0x1
    1654:	39000003          	lb	zero,912(zero) # 390 <main-0x11fffc70>
    1658:	00014e0f          	.insn	4, 0x00014e0f
    165c:	0100                	addi	s0,sp,128
    165e:	085a                	slli	a6,a6,0x16
    1660:	00637273          	csrrci	tp,0x6,6
    1664:	2139                	addiw	sp,sp,14
    1666:	000000eb          	.insn	4, 0x00eb
    166a:	5b01                	li	s6,-32
    166c:	6e01                	.insn	2, 0x6e01
    166e:	3900                	fld	fs0,48(a0)
    1670:	922c                	.insn	2, 0x922c
    1672:	0000                	unimp
    1674:	5600                	lw	s0,40(a2)
    1676:	0009                	c.nop	2
    1678:	5200                	lw	s0,32(a2)
    167a:	0009                	c.nop	2
    167c:	0200                	addi	s0,sp,256
    167e:	0064                	addi	s1,sp,12
    1680:	0b3a                	slli	s6,s6,0xe
    1682:	014e                	slli	sp,sp,0x13
    1684:	0000                	unimp
    1686:	0000096f          	jal	s2,1686 <main-0x11ffe97a>
    168a:	096d                	addi	s2,s2,27 # 101b <main-0x11ffefe5>
    168c:	0000                	unimp
    168e:	6902                	ld	s2,0(sp)
    1690:	3b00                	fld	fs0,48(a4)
    1692:	0000920b          	.insn	4, 0x920b
    1696:	8800                	.insn	2, 0x8800
    1698:	0009                	c.nop	2
    169a:	7c00                	ld	s0,56(s0)
    169c:	0009                	c.nop	2
    169e:	0000                	unimp
    16a0:	e504                	sd	s1,8(a0)
    16a2:	0002                	c.slli64	zero
    16a4:	3200                	fld	fs0,32(a2)
    16a6:	014e                	slli	sp,sp,0x13
    16a8:	0000                	unimp
    16aa:	0710                	addi	a2,sp,896
    16ac:	1200                	addi	s0,sp,288
    16ae:	0000                	unimp
    16b0:	0000                	unimp
    16b2:	0012                	c.slli	zero,0x4
    16b4:	0000                	unimp
    16b6:	0000                	unimp
    16b8:	0000                	unimp
    16ba:	9c01                	subw	s0,s0,s0
    16bc:	00000213          	li	tp,0
    16c0:	0206                	slli	tp,tp,0x1
    16c2:	32000003          	lb	zero,800(zero) # 320 <main-0x11fffce0>
    16c6:	4e0e                	lw	t3,192(sp)
    16c8:	0001                	nop
    16ca:	0100                	addi	s0,sp,128
    16cc:	015a                	slli	sp,sp,0x16
    16ce:	00637273          	csrrci	tp,0x6,6
    16d2:	2032                	fld	ft0,264(sp)
    16d4:	000000eb          	.insn	4, 0x00eb
    16d8:	09c6                	slli	s3,s3,0x11
    16da:	0000                	unimp
    16dc:	09c2                	slli	s3,s3,0x10
    16de:	0000                	unimp
    16e0:	6402                	ld	s0,0(sp)
    16e2:	3300                	fld	fs0,32(a4)
    16e4:	00014e0b          	.insn	4, 0x00014e0b
    16e8:	de00                	sw	s0,56(a2)
    16ea:	0009                	c.nop	2
    16ec:	da00                	sw	s0,48(a2)
    16ee:	0009                	c.nop	2
    16f0:	0000                	unimp
    16f2:	3c04                	fld	fs1,56(s0)
    16f4:	0002                	c.slli64	zero
    16f6:	2900                	fld	fs0,16(a0)
    16f8:	0092                	slli	ra,ra,0x4
    16fa:	0000                	unimp
    16fc:	06f6                	slli	a3,a3,0x1d
    16fe:	1200                	addi	s0,sp,288
    1700:	0000                	unimp
    1702:	0000                	unimp
    1704:	001a                	c.slli	zero,0x6
    1706:	0000                	unimp
    1708:	0000                	unimp
    170a:	0000                	unimp
    170c:	9c01                	subw	s0,s0,s0
    170e:	0256                	slli	tp,tp,0x15
    1710:	0000                	unimp
    1712:	7301                	lui	t1,0xfffe0
    1714:	2900                	fld	fs0,16(a0)
    1716:	eb14                	sd	a3,16(a4)
    1718:	0000                	unimp
    171a:	fa00                	sd	s0,48(a2)
    171c:	0009                	c.nop	2
    171e:	f200                	sd	s0,32(a2)
    1720:	0009                	c.nop	2
    1722:	0200                	addi	s0,sp,256
    1724:	0070                	addi	a2,sp,12
    1726:	112a                	slli	sp,sp,0x2a
    1728:	000000eb          	.insn	4, 0x00eb
    172c:	0a26                	slli	s4,s4,0x9
    172e:	0000                	unimp
    1730:	0a1e                	slli	s4,s4,0x7
    1732:	0000                	unimp
    1734:	0400                	addi	s0,sp,512
    1736:	02de                	slli	t0,t0,0x17
    1738:	0000                	unimp
    173a:	9c1d                	subw	s0,s0,a5
    173c:	0000                	unimp
    173e:	d200                	sw	s0,32(a2)
    1740:	0006                	c.slli	zero,0x1
    1742:	0012                	c.slli	zero,0x4
    1744:	0000                	unimp
    1746:	2400                	fld	fs0,8(s0)
    1748:	0000                	unimp
    174a:	0000                	unimp
    174c:	0000                	unimp
    174e:	0100                	addi	s0,sp,128
    1750:	f39c                	sd	a5,32(a5)
    1752:	0002                	c.slli64	zero
    1754:	0100                	addi	s0,sp,128
    1756:	1d003173          	csrrc	sp,0x1d0,zero
    175a:	f314                	sd	a3,32(a4)
    175c:	0002                	c.slli64	zero
    175e:	4b00                	lw	s0,16(a4)
    1760:	000a                	c.slli	zero,0x2
    1762:	4700                	lw	s0,8(a4)
    1764:	000a                	c.slli	zero,0x2
    1766:	0100                	addi	s0,sp,128
    1768:	1d003273          	csrrc	tp,0x1d0,zero
    176c:	f324                	sd	s1,96(a4)
    176e:	0002                	c.slli64	zero
    1770:	6600                	ld	s0,8(a2)
    1772:	000a                	c.slli	zero,0x2
    1774:	6200                	ld	s0,0(a2)
    1776:	000a                	c.slli	zero,0x2
    1778:	0100                	addi	s0,sp,128
    177a:	006e                	c.slli	zero,0x1b
    177c:	2e1d                	addiw	t3,t3,7 # 1a007 <main-0x11fe5ff9>
    177e:	0092                	slli	ra,ra,0x4
    1780:	0000                	unimp
    1782:	0a81                	addi	s5,s5,0
    1784:	0000                	unimp
    1786:	0a7d                	addi	s4,s4,31
    1788:	0000                	unimp
    178a:	7002                	.insn	2, 0x7002
    178c:	0031                	c.nop	12
    178e:	0f1e                	slli	t5,t5,0x7
    1790:	02f9                	addi	t0,t0,30
    1792:	0000                	unimp
    1794:	0a9c                	addi	a5,sp,336
    1796:	0000                	unimp
    1798:	0a98                	addi	a4,sp,336
    179a:	0000                	unimp
    179c:	7002                	.insn	2, 0x7002
    179e:	0032                	c.slli	zero,0xc
    17a0:	0f1f 02f9 0000      	.insn	6, 0x02f90f1f
    17a6:	00000ab7          	lui	s5,0x0
    17aa:	00000ab3          	add	s5,zero,zero
    17ae:	d20d                	beqz	a2,16d0 <main-0x11ffe930>
    17b0:	0006                	c.slli	zero,0x1
    17b2:	0012                	c.slli	zero,0x4
    17b4:	0000                	unimp
    17b6:	2000                	fld	fs0,0(s0)
    17b8:	0000                	unimp
    17ba:	0000                	unimp
    17bc:	0000                	unimp
    17be:	0200                	addi	s0,sp,256
    17c0:	0069                	c.nop	26
    17c2:	1020                	addi	s0,sp,40
    17c4:	0092                	slli	ra,ra,0x4
    17c6:	0000                	unimp
    17c8:	0ad6                	slli	s5,s5,0x15
    17ca:	0000                	unimp
    17cc:	0ace                	slli	s5,s5,0x13
    17ce:	0000                	unimp
    17d0:	0000                	unimp
    17d2:	f805                	bnez	s0,1702 <main-0x11ffe8fe>
    17d4:	0002                	c.slli64	zero
    17d6:	0e00                	addi	s0,sp,784
    17d8:	3305                	addiw	t1,t1,-31 # fffffffffffdffe1 <__sheap+0xffffffffedfdcfe1>
    17da:	0000                	unimp
    17dc:	0400                	addi	s0,sp,512
    17de:	030e                	slli	t1,t1,0x3
    17e0:	0000                	unimp
    17e2:	00037213          	andi	tp,t1,0
    17e6:	ba00                	fsd	fs0,48(a2)
    17e8:	0006                	c.slli	zero,0x1
    17ea:	0012                	c.slli	zero,0x4
    17ec:	0000                	unimp
    17ee:	1800                	addi	s0,sp,48
    17f0:	0000                	unimp
    17f2:	0000                	unimp
    17f4:	0000                	unimp
    17f6:	0100                	addi	s0,sp,128
    17f8:	729c                	ld	a5,32(a3)
    17fa:	06000003          	lb	zero,96(zero) # 60 <main-0x11ffffa0>
    17fe:	0302                	c.slli64	t1
    1800:	0000                	unimp
    1802:	03720e13          	addi	t3,tp,55 # 37 <main-0x11ffffc9>
    1806:	0000                	unimp
    1808:	5a01                	li	s4,-32
    180a:	7301                	lui	t1,0xfffe0
    180c:	6372                	ld	t1,280(sp)
    180e:	1300                	addi	s0,sp,416
    1810:	f320                	sd	s0,96(a4)
    1812:	0002                	c.slli64	zero
    1814:	0d00                	addi	s0,sp,656
    1816:	0900000b          	.insn	4, 0x0900000b
    181a:	0100000b          	.insn	4, 0x0100000b
    181e:	006e                	c.slli	zero,0x1b
    1820:	00922b13          	slti	s6,tp,9
    1824:	0000                	unimp
    1826:	0b2a                	slli	s6,s6,0xa
    1828:	0000                	unimp
    182a:	0b24                	addi	s1,sp,408
    182c:	0000                	unimp
    182e:	6402                	ld	s0,0(sp)
    1830:	1400                	addi	s0,sp,544
    1832:	7409                	lui	s0,0xfffe2
    1834:	52000003          	lb	zero,1312(zero) # 520 <main-0x11fffae0>
    1838:	4a00000b          	.insn	4, 0x4a00000b
    183c:	0200000b          	.insn	4, 0x0200000b
    1840:	0f150073          	.insn	4, 0x0f150073
    1844:	02f9                	addi	t0,t0,30
    1846:	0000                	unimp
    1848:	0b74                	addi	a3,sp,412
    184a:	0000                	unimp
    184c:	0b72                	slli	s6,s6,0x1c
    184e:	0000                	unimp
    1850:	0f00                	addi	s0,sp,912
    1852:	0508                	addi	a0,sp,640
    1854:	002a                	c.slli	zero,0xa
    1856:	0000                	unimp
    1858:	fb10                	sd	a2,48(a4)
    185a:	0002                	c.slli64	zero
    185c:	0100                	addi	s0,sp,128
    185e:	010a                	slli	sp,sp,0x2
    1860:	0372                	slli	t1,t1,0x1c
    1862:	0000                	unimp
    1864:	06a8                	addi	a0,sp,840
    1866:	1200                	addi	s0,sp,288
    1868:	0000                	unimp
    186a:	0000                	unimp
    186c:	0012                	c.slli	zero,0x4
    186e:	0000                	unimp
    1870:	0000                	unimp
    1872:	0000                	unimp
    1874:	9c01                	subw	s0,s0,s0
    1876:	7308                	ld	a0,32(a4)
    1878:	0a00                	addi	s0,sp,272
    187a:	720e                	ld	tp,224(sp)
    187c:	01000003          	lb	zero,16(zero) # 10 <main-0x11fffff0>
    1880:	085a                	slli	a6,a6,0x16
    1882:	140a0063          	beqz	s4,19c2 <main-0x11ffe63e>
    1886:	002a                	c.slli	zero,0xa
    1888:	0000                	unimp
    188a:	5b01                	li	s6,-32
    188c:	6e01                	.insn	2, 0x6e01
    188e:	0a00                	addi	s0,sp,272
    1890:	921d                	srli	a2,a2,0x27
    1892:	0000                	unimp
    1894:	8d00                	.insn	2, 0x8d00
    1896:	8100000b          	.insn	4, 0x8100000b
    189a:	0200000b          	.insn	4, 0x0200000b
    189e:	0070                	addi	a2,sp,12
    18a0:	0374090b          	.insn	4, 0x0374090b
    18a4:	0000                	unimp
    18a6:	0bdd                	addi	s7,s7,23
    18a8:	0000                	unimp
    18aa:	0bd9                	addi	s7,s7,22
    18ac:	0000                	unimp
	...

Disassembly of section .debug_abbrev:

0000000000000000 <.debug_abbrev>:
   0:	2401                	sext.w	s0,s0
   2:	0b00                	addi	s0,sp,400
   4:	030b3e0b          	.insn	4, 0x030b3e0b
   8:	000e                	c.slli	zero,0x3
   a:	0200                	addi	s0,sp,256
   c:	210b000f          	.insn	4, 0x210b000f
  10:	4908                	lw	a0,16(a0)
  12:	03000013          	li	zero,48
  16:	0016                	c.slli	zero,0x5
  18:	213a0803          	lb	a6,531(s4)
  1c:	3b02                	fld	fs6,32(sp)
  1e:	1d21390b          	.insn	4, 0x1d21390b
  22:	1349                	addi	t1,t1,-14 # fffffffffffdfff2 <__sheap+0xffffffffedfdcff2>
  24:	0000                	unimp
  26:	0504                	addi	s1,sp,640
  28:	0300                	addi	s0,sp,384
  2a:	3a0e                	fld	fs4,224(sp)
  2c:	0121                	addi	sp,sp,8
  2e:	390a213b          	.insn	4, 0x390a213b
  32:	0213490b          	.insn	4, 0x0213490b
  36:	1742b717          	auipc	a4,0x1742b
  3a:	0000                	unimp
  3c:	4805                	li	a6,1
  3e:	7d01                	lui	s10,0xfffe0
  40:	7f01                	lui	t5,0xfffe0
  42:	00130113          	addi	sp,t1,1
  46:	0600                	addi	s0,sp,768
  48:	0049                	c.nop	18
  4a:	1802                	slli	a6,a6,0x20
  4c:	187e                	slli	a6,a6,0x3f
  4e:	0000                	unimp
  50:	25011107          	.insn	4, 0x25011107
  54:	130e                	slli	t1,t1,0x23
  56:	1b1f030b          	.insn	4, 0x1b1f030b
  5a:	551f 1117 1001      	.insn	6, 0x10011117551f
  60:	08000017          	auipc	zero,0x8000
  64:	0024                	addi	s1,sp,8
  66:	0b3e0b0b          	.insn	4, 0x0b3e0b0b
  6a:	00000803          	lb	a6,0(zero) # 0 <main-0x12000000>
  6e:	1609                	addi	a2,a2,-30
  70:	0300                	addi	s0,sp,384
  72:	3a0e                	fld	fs4,224(sp)
  74:	390b3b0b          	.insn	4, 0x390b3b0b
  78:	0013490b          	.insn	4, 0x0013490b
  7c:	0a00                	addi	s0,sp,272
  7e:	0034                	addi	a3,sp,8
  80:	0b3a0e03          	lb	t3,179(s4)
  84:	0b390b3b          	.insn	4, 0x0b390b3b
  88:	1349                	addi	t1,t1,-14
  8a:	1802193f 2e0b0000 	.insn	8, 0x2e0b00001802193f
  92:	3f00                	fld	fs0,56(a4)
  94:	0319                	addi	t1,t1,6
  96:	3a0e                	fld	fs4,224(sp)
  98:	390b3b0b          	.insn	4, 0x390b3b0b
  9c:	3c19270b          	.insn	4, 0x3c19270b
  a0:	0019                	c.nop	6
  a2:	0c00                	addi	s0,sp,528
  a4:	012e                	slli	sp,sp,0xb
  a6:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
  ae:	0b39                	addi	s6,s6,14 # 700e <main-0x11ff8ff2>
  b0:	13491927          	.insn	4, 0x13491927
  b4:	193c                	addi	a5,sp,184
  b6:	1301                	addi	t1,t1,-32
  b8:	0000                	unimp
  ba:	050d                	addi	a0,a0,3
  bc:	4900                	lw	s0,16(a0)
  be:	0e000013          	li	zero,224
  c2:	0018                	.insn	2, 0x0018
  c4:	0000                	unimp
  c6:	4900260f          	.insn	4, 0x4900260f
  ca:	10000013          	li	zero,256
  ce:	012e                	slli	sp,sp,0xb
  d0:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
  d8:	0b39                	addi	s6,s6,14
  da:	13491927          	.insn	4, 0x13491927
  de:	0111                	addi	sp,sp,4
  e0:	0712                	slli	a4,a4,0x4
  e2:	1840                	addi	s0,sp,52
  e4:	197a                	slli	s2,s2,0x3e
  e6:	1301                	addi	t1,t1,-32
  e8:	0000                	unimp
  ea:	4811                	li	a6,4
  ec:	7d00                	ld	s0,56(a0)
  ee:	7f01                	lui	t5,0xfffe0
  f0:	00000013          	nop
  f4:	4901                	li	s2,0
  f6:	0200                	addi	s0,sp,256
  f8:	7e18                	ld	a4,56(a2)
  fa:	0018                	.insn	2, 0x0018
  fc:	0200                	addi	s0,sp,256
  fe:	0148                	addi	a0,sp,132
 100:	017d                	addi	sp,sp,31
 102:	0000137f 0b002403 	.insn	12, 0x030b3e0b0b0024030000137f
 10a:	030b3e0b 
 10e:	000e                	c.slli	zero,0x3
 110:	0400                	addi	s0,sp,512
 112:	1755010b          	.insn	4, 0x1755010b
 116:	1301                	addi	t1,t1,-32
 118:	0000                	unimp
 11a:	3405                	addiw	s0,s0,-31 # fffffffffffe1fe1 <__sheap+0xffffffffedfdefe1>
 11c:	0300                	addi	s0,sp,384
 11e:	3a08                	fld	fa0,48(a2)
 120:	0121                	addi	sp,sp,8
 122:	0b390b3b          	.insn	4, 0x0b390b3b
 126:	1349                	addi	t1,t1,-14
 128:	0000                	unimp
 12a:	3406                	fld	fs0,96(sp)
 12c:	0300                	addi	s0,sp,384
 12e:	3a08                	fld	fa0,48(a2)
 130:	0121                	addi	sp,sp,8
 132:	0b390b3b          	.insn	4, 0x0b390b3b
 136:	1349                	addi	t1,t1,-14
 138:	1702                	slli	a4,a4,0x20
 13a:	001742b7          	lui	t0,0x174
 13e:	0700                	addi	s0,sp,896
 140:	011d                	addi	sp,sp,7
 142:	1331                	addi	t1,t1,-20
 144:	0152                	slli	sp,sp,0x14
 146:	42b8                	lw	a4,64(a3)
 148:	5817550b          	.insn	4, 0x5817550b
 14c:	0121                	addi	sp,sp,8
 14e:	0b59                	addi	s6,s6,22
 150:	00000b57          	.insn	4, 0x0b57
 154:	3408                	fld	fa0,40(s0)
 156:	3100                	fld	fs0,32(a0)
 158:	b7170213          	addi	tp,a4,-1167 # 1742aba7 <__sheap+0x5427ba7>
 15c:	1742                	slli	a4,a4,0x30
 15e:	0000                	unimp
 160:	0509                	addi	a0,a0,2
 162:	3100                	fld	fs0,32(a0)
 164:	b7170213          	addi	tp,a4,-1167
 168:	1742                	slli	a4,a4,0x30
 16a:	0000                	unimp
 16c:	340a                	fld	fs0,160(sp)
 16e:	0300                	addi	s0,sp,384
 170:	3a08                	fld	fa0,48(a2)
 172:	0121                	addi	sp,sp,8
 174:	0b390b3b          	.insn	4, 0x0b390b3b
 178:	1349                	addi	t1,t1,-14
 17a:	1802                	slli	a6,a6,0x20
 17c:	0000                	unimp
 17e:	0300050b          	.insn	4, 0x0300050b
 182:	3a08                	fld	fa0,48(a2)
 184:	0121                	addi	sp,sp,8
 186:	0b390b3b          	.insn	4, 0x0b390b3b
 18a:	1349                	addi	t1,t1,-14
 18c:	1702                	slli	a4,a4,0x20
 18e:	001742b7          	lui	t0,0x174
 192:	0c00                	addi	s0,sp,528
 194:	0034                	addi	a3,sp,8
 196:	213a0e03          	lb	t3,531(s4)
 19a:	3b01                	addiw	s6,s6,-32
 19c:	490b390b          	.insn	4, 0x490b390b
 1a0:	b7170213          	addi	tp,a4,-1167
 1a4:	1742                	slli	a4,a4,0x30
 1a6:	0000                	unimp
 1a8:	160d                	addi	a2,a2,-29
 1aa:	0300                	addi	s0,sp,384
 1ac:	3a0e                	fld	fs4,224(sp)
 1ae:	390b3b0b          	.insn	4, 0x390b3b0b
 1b2:	0013490b          	.insn	4, 0x0013490b
 1b6:	0e00                	addi	s0,sp,784
 1b8:	0111010b          	.insn	4, 0x0111010b
 1bc:	0712                	slli	a4,a4,0x4
 1be:	1301                	addi	t1,t1,-32
 1c0:	0000                	unimp
 1c2:	7d00480f          	.insn	4, 0x7d00480f
 1c6:	7f01                	lui	t5,0xfffe0
 1c8:	10000013          	li	zero,256
 1cc:	011d                	addi	sp,sp,7
 1ce:	1331                	addi	t1,t1,-20
 1d0:	0152                	slli	sp,sp,0x14
 1d2:	42b8                	lw	a4,64(a3)
 1d4:	5817550b          	.insn	4, 0x5817550b
 1d8:	0121                	addi	sp,sp,8
 1da:	0b59                	addi	s6,s6,22
 1dc:	13010b57          	.insn	4, 0x13010b57
 1e0:	0000                	unimp
 1e2:	1611                	addi	a2,a2,-28
 1e4:	0300                	addi	s0,sp,384
 1e6:	3a08                	fld	fa0,48(a2)
 1e8:	0321                	addi	t1,t1,8
 1ea:	21390b3b          	.insn	4, 0x21390b3b
 1ee:	491d                	li	s2,7
 1f0:	12000013          	li	zero,288
 1f4:	0101                	addi	sp,sp,0
 1f6:	1349                	addi	t1,t1,-14
 1f8:	1301                	addi	t1,t1,-32
 1fa:	0000                	unimp
 1fc:	49002113          	slti	sp,zero,1168
 200:	000b2f13          	slti	t5,s6,0
 204:	1400                	addi	s0,sp,544
 206:	0034                	addi	a3,sp,8
 208:	213a0e03          	lb	t3,531(s4)
 20c:	3b01                	addiw	s6,s6,-32
 20e:	490b390b          	.insn	4, 0x490b390b
 212:	00180213          	addi	tp,a6,1
 216:	1500                	addi	s0,sp,672
 218:	0005                	c.nop	1
 21a:	1349                	addi	t1,t1,-14
 21c:	0000                	unimp
 21e:	1816                	slli	a6,a6,0x25
 220:	0000                	unimp
 222:	1700                	addi	s0,sp,928
 224:	012e                	slli	sp,sp,0xb
 226:	0e03193f 3b01213a 	.insn	8, 0x3b01213a0e03193f
 22e:	0121390b          	.insn	4, 0x0121390b
 232:	13491927          	.insn	4, 0x13491927
 236:	0111                	addi	sp,sp,4
 238:	0712                	slli	a4,a4,0x4
 23a:	1840                	addi	s0,sp,52
 23c:	197a                	slli	s2,s2,0x3e
 23e:	1301                	addi	t1,t1,-32
 240:	0000                	unimp
 242:	4818                	lw	a4,16(s0)
 244:	7d01                	lui	s10,0xfffe0
 246:	7f01                	lui	t5,0xfffe0
 248:	00130113          	addi	sp,t1,1
 24c:	1900                	addi	s0,sp,176
 24e:	011d                	addi	sp,sp,7
 250:	1331                	addi	t1,t1,-20
 252:	0152                	slli	sp,sp,0x14
 254:	42b8                	lw	a4,64(a3)
 256:	1201110b          	.insn	4, 0x1201110b
 25a:	01215807          	.insn	4, 0x01215807
 25e:	2159                	addiw	sp,sp,22
 260:	5718                	lw	a4,40(a4)
 262:	0921                	addi	s2,s2,8
 264:	0000                	unimp
 266:	051a                	slli	a0,a0,0x6
 268:	0300                	addi	s0,sp,384
 26a:	3a0e                	fld	fs4,224(sp)
 26c:	0121                	addi	sp,sp,8
 26e:	3930213b          	.insn	4, 0x3930213b
 272:	0213490b          	.insn	4, 0x0213490b
 276:	1742b717          	auipc	a4,0x1742b
 27a:	0000                	unimp
 27c:	3100341b          	.insn	4, 0x3100341b
 280:	1c000013          	li	zero,448
 284:	012e                	slli	sp,sp,0xb
 286:	213a0e03          	lb	t3,531(s4)
 28a:	3b01                	addiw	s6,s6,-32
 28c:	0121390b          	.insn	4, 0x0121390b
 290:	13491927          	.insn	4, 0x13491927
 294:	2120                	fld	fs0,64(a0)
 296:	0101                	addi	sp,sp,0
 298:	1d000013          	li	zero,464
 29c:	0005                	c.nop	1
 29e:	213a0803          	lb	a6,531(s4)
 2a2:	3b01                	addiw	s6,s6,-32
 2a4:	490b390b          	.insn	4, 0x490b390b
 2a8:	1e000013          	li	zero,480
 2ac:	0111                	addi	sp,sp,4
 2ae:	0e25                	addi	t3,t3,9
 2b0:	1f030b13          	addi	s6,t1,496
 2b4:	01111f1b          	slliw	t5,sp,0x11
 2b8:	0712                	slli	a4,a4,0x4
 2ba:	1710                	addi	a2,sp,928
 2bc:	0000                	unimp
 2be:	0f1f 0b00 030b      	.insn	6, 0x030b0b000f1f
 2c4:	000e                	c.slli	zero,0x3
 2c6:	2000                	fld	fs0,0(s0)
 2c8:	0024                	addi	s1,sp,8
 2ca:	0b3e0b0b          	.insn	4, 0x0b3e0b0b
 2ce:	00000803          	lb	a6,0(zero) # 0 <main-0x12000000>
 2d2:	2621                	addiw	a2,a2,8
 2d4:	4900                	lw	s0,16(a0)
 2d6:	22000013          	li	zero,544
 2da:	012e                	slli	sp,sp,0xb
 2dc:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 2e4:	0b39                	addi	s6,s6,14
 2e6:	13491927          	.insn	4, 0x13491927
 2ea:	193c                	addi	a5,sp,184
 2ec:	1301                	addi	t1,t1,-32
 2ee:	0000                	unimp
 2f0:	0b000f23          	sb	a6,190(zero) # be <main-0x11ffff42>
 2f4:	0013490b          	.insn	4, 0x0013490b
 2f8:	2400                	fld	fs0,8(s0)
 2fa:	012e                	slli	sp,sp,0xb
 2fc:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 304:	0b39                	addi	s6,s6,14
 306:	193c1927          	.insn	4, 0x193c1927
 30a:	1301                	addi	t1,t1,-32
 30c:	0000                	unimp
 30e:	0525                	addi	a0,a0,9
 310:	3100                	fld	fs0,32(a0)
 312:	00180213          	addi	tp,a6,1
 316:	2600                	fld	fs0,8(a2)
 318:	0b0b000f          	.insn	4, 0x0b0b000f
 31c:	0000                	unimp
 31e:	03012e27          	fsw	fa6,60(sp)
 322:	3a0e                	fld	fs4,224(sp)
 324:	390b3b0b          	.insn	4, 0x390b3b0b
 328:	4919270b          	.insn	4, 0x4919270b
 32c:	12011113          	.insn	4, 0x12011113
 330:	7a184007          	.insn	4, 0x7a184007
 334:	0119                	addi	sp,sp,6
 336:	28000013          	li	zero,640
 33a:	012e                	slli	sp,sp,0xb
 33c:	0b3a0e03          	lb	t3,179(s4)
 340:	0b390b3b          	.insn	4, 0x0b390b3b
 344:	0b201927          	.insn	4, 0x0b201927
 348:	1301                	addi	t1,t1,-32
 34a:	0000                	unimp
 34c:	2e29                	addiw	t3,t3,10
 34e:	3101                	addiw	sp,sp,-32
 350:	12011113          	.insn	4, 0x12011113
 354:	7a184007          	.insn	4, 0x7a184007
 358:	0119                	addi	sp,sp,6
 35a:	2a000013          	li	zero,672
 35e:	0036                	c.slli	zero,0xd
 360:	1802                	slli	a6,a6,0x20
 362:	0000                	unimp
 364:	0100                	addi	s0,sp,128
 366:	0024                	addi	s1,sp,8
 368:	0b3e0b0b          	.insn	4, 0x0b3e0b0b
 36c:	00000e03          	lb	t3,0(zero) # 0 <main-0x12000000>
 370:	0502                	c.slli64	a0
 372:	3100                	fld	fs0,32(a0)
 374:	b7170213          	addi	tp,a4,-1167 # 1742ade7 <__sheap+0x5427de7>
 378:	1742                	slli	a4,a4,0x30
 37a:	0000                	unimp
 37c:	31003403          	ld	s0,784(zero) # 310 <main-0x11fffcf0>
 380:	00180213          	addi	tp,a6,1
 384:	0400                	addi	s0,sp,512
 386:	0005                	c.nop	1
 388:	213a0e03          	lb	t3,531(s4)
 38c:	390b3b03          	ld	s6,912(s6)
 390:	0013490b          	.insn	4, 0x0013490b
 394:	0500                	addi	s0,sp,640
 396:	0034                	addi	a3,sp,8
 398:	213a0803          	lb	a6,531(s4)
 39c:	390b3b03          	ld	s6,912(s6)
 3a0:	1221                	addi	tp,tp,-24 # ffffffffffffffe8 <__sheap+0xffffffffedffcfe8>
 3a2:	1349                	addi	t1,t1,-14
 3a4:	0000                	unimp
 3a6:	1606                	slli	a2,a2,0x21
 3a8:	0300                	addi	s0,sp,384
 3aa:	3a08                	fld	fa0,48(a2)
 3ac:	0421                	addi	s0,s0,8
 3ae:	21390b3b          	.insn	4, 0x21390b3b
 3b2:	491d                	li	s2,7
 3b4:	07000013          	li	zero,112
 3b8:	0016                	c.slli	zero,0x5
 3ba:	213a0e03          	lb	t3,531(s4)
 3be:	3b04                	fld	fs1,48(a4)
 3c0:	0d21390b          	.insn	4, 0x0d21390b
 3c4:	1349                	addi	t1,t1,-14
 3c6:	0000                	unimp
 3c8:	0508                	addi	a0,sp,640
 3ca:	0300                	addi	s0,sp,384
 3cc:	3a08                	fld	fa0,48(a2)
 3ce:	0221                	addi	tp,tp,8 # 8 <main-0x11fffff8>
 3d0:	3920213b          	.insn	4, 0x3920213b
 3d4:	0013490b          	.insn	4, 0x0013490b
 3d8:	0900                	addi	s0,sp,144
 3da:	0111                	addi	sp,sp,4
 3dc:	0e25                	addi	t3,t3,9
 3de:	1f030b13          	addi	s6,t1,496
 3e2:	01111f1b          	slliw	t5,sp,0x11
 3e6:	0712                	slli	a4,a4,0x4
 3e8:	1710                	addi	a2,sp,928
 3ea:	0000                	unimp
 3ec:	240a                	fld	fs0,128(sp)
 3ee:	0b00                	addi	s0,sp,400
 3f0:	030b3e0b          	.insn	4, 0x030b3e0b
 3f4:	0008                	.insn	2, 0x0008
 3f6:	0b00                	addi	s0,sp,400
 3f8:	012e                	slli	sp,sp,0xb
 3fa:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 402:	0b39                	addi	s6,s6,14
 404:	13491927          	.insn	4, 0x13491927
 408:	193c                	addi	a5,sp,184
 40a:	1301                	addi	t1,t1,-32
 40c:	0000                	unimp
 40e:	050c                	addi	a1,sp,640
 410:	4900                	lw	s0,16(a0)
 412:	0d000013          	li	zero,208
 416:	0b0b000f          	.insn	4, 0x0b0b000f
 41a:	1349                	addi	t1,t1,-14
 41c:	0000                	unimp
 41e:	260e                	fld	fa2,192(sp)
 420:	4900                	lw	s0,16(a0)
 422:	0f000013          	li	zero,240
 426:	012e                	slli	sp,sp,0xb
 428:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 430:	0b39                	addi	s6,s6,14
 432:	13491927          	.insn	4, 0x13491927
 436:	0111                	addi	sp,sp,4
 438:	0712                	slli	a4,a4,0x4
 43a:	1840                	addi	s0,sp,52
 43c:	197a                	slli	s2,s2,0x3e
 43e:	1301                	addi	t1,t1,-32
 440:	0000                	unimp
 442:	0510                	addi	a2,sp,640
 444:	0300                	addi	s0,sp,384
 446:	3a08                	fld	fa0,48(a2)
 448:	390b3b0b          	.insn	4, 0x390b3b0b
 44c:	0213490b          	.insn	4, 0x0213490b
 450:	1742b717          	auipc	a4,0x1742b
 454:	0000                	unimp
 456:	3411                	addiw	s0,s0,-28
 458:	0300                	addi	s0,sp,384
 45a:	3a08                	fld	fa0,48(a2)
 45c:	390b3b0b          	.insn	4, 0x390b3b0b
 460:	0213490b          	.insn	4, 0x0213490b
 464:	1742b717          	auipc	a4,0x1742b
 468:	0000                	unimp
 46a:	1d12                	slli	s10,s10,0x24
 46c:	3101                	addiw	sp,sp,-32
 46e:	b8015213          	.insn	4, 0xb8015213
 472:	0b42                	slli	s6,s6,0x10
 474:	0111                	addi	sp,sp,4
 476:	0712                	slli	a4,a4,0x4
 478:	0b58                	addi	a4,sp,404
 47a:	0b59                	addi	s6,s6,22
 47c:	13010b57          	.insn	4, 0x13010b57
 480:	0000                	unimp
 482:	31011d13          	.insn	4, 0x31011d13
 486:	b8015213          	.insn	4, 0xb8015213
 48a:	0b42                	slli	s6,s6,0x10
 48c:	0111                	addi	sp,sp,4
 48e:	0712                	slli	a4,a4,0x4
 490:	0b58                	addi	a4,sp,404
 492:	0b59                	addi	s6,s6,22
 494:	00000b57          	.insn	4, 0x0b57
 498:	4814                	lw	a3,16(s0)
 49a:	7d01                	lui	s10,0xfffe0
 49c:	7f01                	lui	t5,0xfffe0
 49e:	15000013          	li	zero,336
 4a2:	0049                	c.nop	18
 4a4:	1802                	slli	a6,a6,0x20
 4a6:	187e                	slli	a6,a6,0x3f
 4a8:	0000                	unimp
 4aa:	2e16                	fld	ft8,320(sp)
 4ac:	0301                	addi	t1,t1,0
 4ae:	3a0e                	fld	fs4,224(sp)
 4b0:	390b3b0b          	.insn	4, 0x390b3b0b
 4b4:	4919270b          	.insn	4, 0x4919270b
 4b8:	010b2013          	slti	zero,s6,16
 4bc:	17000013          	li	zero,368
 4c0:	012e                	slli	sp,sp,0xb
 4c2:	0b3a0e03          	lb	t3,179(s4)
 4c6:	0b390b3b          	.insn	4, 0x0b390b3b
 4ca:	13491927          	.insn	4, 0x13491927
 4ce:	0b20                	addi	s0,sp,408
 4d0:	0000                	unimp
 4d2:	0100                	addi	s0,sp,128
 4d4:	0024                	addi	s1,sp,8
 4d6:	0b3e0b0b          	.insn	4, 0x0b3e0b0b
 4da:	00000e03          	lb	t3,0(zero) # 0 <main-0x12000000>
 4de:	1602                	slli	a2,a2,0x20
 4e0:	0300                	addi	s0,sp,384
 4e2:	3a0e                	fld	fs4,224(sp)
 4e4:	390b3b0b          	.insn	4, 0x390b3b0b
 4e8:	0013490b          	.insn	4, 0x0013490b
 4ec:	0300                	addi	s0,sp,384
 4ee:	0005                	c.nop	1
 4f0:	1349                	addi	t1,t1,-14
 4f2:	0000                	unimp
 4f4:	2e04                	fld	fs1,24(a2)
 4f6:	3f01                	addiw	t5,t5,-32 # fffffffffffdffe0 <__sheap+0xffffffffedfdcfe0>
 4f8:	0319                	addi	t1,t1,6
 4fa:	3a0e                	fld	fs4,224(sp)
 4fc:	0421                	addi	s0,s0,8
 4fe:	21390b3b          	.insn	4, 0x21390b3b
 502:	2709                	addiw	a4,a4,2 # 1742b466 <__sheap+0x5428466>
 504:	4919                	li	s2,6
 506:	01193c13          	sltiu	s8,s2,17
 50a:	05000013          	li	zero,80
 50e:	0018                	.insn	2, 0x0018
 510:	0000                	unimp
 512:	4806                	lw	a6,64(sp)
 514:	7d00                	ld	s0,56(a0)
 516:	7f01                	lui	t5,0xfffe0
 518:	07000013          	li	zero,112
 51c:	0148                	addi	a0,sp,132
 51e:	017d                	addi	sp,sp,31
 520:	1301137f 49080000 	.insn	12, 0x7e180200490800001301137f
 528:	7e180200 
 52c:	0018                	.insn	2, 0x0018
 52e:	0900                	addi	s0,sp,144
 530:	0111                	addi	sp,sp,4
 532:	0e25                	addi	t3,t3,9
 534:	1f030b13          	addi	s6,t1,496
 538:	01111f1b          	slliw	t5,sp,0x11
 53c:	0712                	slli	a4,a4,0x4
 53e:	1710                	addi	a2,sp,928
 540:	0000                	unimp
 542:	0f0a                	slli	t5,t5,0x2
 544:	0b00                	addi	s0,sp,400
 546:	000e030b          	.insn	4, 0x000e030b
 54a:	0b00                	addi	s0,sp,400
 54c:	0024                	addi	s1,sp,8
 54e:	0b3e0b0b          	.insn	4, 0x0b3e0b0b
 552:	00000803          	lb	a6,0(zero) # 0 <main-0x12000000>
 556:	160c                	addi	a1,sp,800
 558:	0300                	addi	s0,sp,384
 55a:	3a08                	fld	fa0,48(a2)
 55c:	390b3b0b          	.insn	4, 0x390b3b0b
 560:	0013490b          	.insn	4, 0x0013490b
 564:	0d00                	addi	s0,sp,656
 566:	002e                	c.slli	zero,0xb
 568:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 570:	0b39                	addi	s6,s6,14
 572:	01871927          	.insn	4, 0x01871927
 576:	3c19                	addiw	s8,s8,-26 # efe6 <main-0x11ff101a>
 578:	0019                	c.nop	6
 57a:	0e00                	addi	s0,sp,784
 57c:	0b0b000f          	.insn	4, 0x0b0b000f
 580:	1349                	addi	t1,t1,-14
 582:	0000                	unimp
 584:	4900260f          	.insn	4, 0x4900260f
 588:	10000013          	li	zero,256
 58c:	012e                	slli	sp,sp,0xb
 58e:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 596:	0b39                	addi	s6,s6,14
 598:	01871927          	.insn	4, 0x01871927
 59c:	1119                	addi	sp,sp,-26
 59e:	1201                	addi	tp,tp,-32 # ffffffffffffffe0 <__sheap+0xffffffffedffcfe0>
 5a0:	7a184007          	.insn	4, 0x7a184007
 5a4:	0119                	addi	sp,sp,6
 5a6:	11000013          	li	zero,272
 5aa:	012e                	slli	sp,sp,0xb
 5ac:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 5b4:	0b39                	addi	s6,s6,14
 5b6:	01871927          	.insn	4, 0x01871927
 5ba:	1119                	addi	sp,sp,-26
 5bc:	1201                	addi	tp,tp,-32 # ffffffffffffffe0 <__sheap+0xffffffffedffcfe0>
 5be:	7a184007          	.insn	4, 0x7a184007
 5c2:	0019                	c.nop	6
 5c4:	1200                	addi	s0,sp,288
 5c6:	0005                	c.nop	1
 5c8:	0b3a0803          	lb	a6,179(s4)
 5cc:	0b390b3b          	.insn	4, 0x0b390b3b
 5d0:	1349                	addi	t1,t1,-14
 5d2:	1702                	slli	a4,a4,0x20
 5d4:	001742b7          	lui	t0,0x174
 5d8:	1300                	addi	s0,sp,416
 5da:	0034                	addi	a3,sp,8
 5dc:	0b3a0803          	lb	a6,179(s4)
 5e0:	0b390b3b          	.insn	4, 0x0b390b3b
 5e4:	1349                	addi	t1,t1,-14
 5e6:	1802                	slli	a6,a6,0x20
 5e8:	0000                	unimp
 5ea:	0100                	addi	s0,sp,128
 5ec:	0034                	addi	a3,sp,8
 5ee:	1331                	addi	t1,t1,-20
 5f0:	1802                	slli	a6,a6,0x20
 5f2:	0000                	unimp
 5f4:	0502                	c.slli64	a0
 5f6:	3100                	fld	fs0,32(a0)
 5f8:	b7170213          	addi	tp,a4,-1167
 5fc:	1742                	slli	a4,a4,0x30
 5fe:	0000                	unimp
 600:	0b002403          	lw	s0,176(zero) # b0 <main-0x11ffff50>
 604:	030b3e0b          	.insn	4, 0x030b3e0b
 608:	000e                	c.slli	zero,0x3
 60a:	0400                	addi	s0,sp,512
 60c:	011d                	addi	sp,sp,7
 60e:	1331                	addi	t1,t1,-20
 610:	0152                	slli	sp,sp,0x14
 612:	42b8                	lw	a4,64(a3)
 614:	1201110b          	.insn	4, 0x1201110b
 618:	590b5807          	.insn	4, 0x590b5807
 61c:	000b570b          	.insn	4, 0x000b570b
 620:	0500                	addi	s0,sp,640
 622:	0005                	c.nop	1
 624:	213a0e03          	lb	t3,531(s4)
 628:	390b3b03          	ld	s6,912(s6)
 62c:	0013490b          	.insn	4, 0x0013490b
 630:	0600                	addi	s0,sp,768
 632:	0034                	addi	a3,sp,8
 634:	213a0803          	lb	a6,531(s4)
 638:	390b3b03          	ld	s6,912(s6)
 63c:	1221                	addi	tp,tp,-24 # ffffffffffffffe8 <__sheap+0xffffffffedffcfe8>
 63e:	1349                	addi	t1,t1,-14
 640:	0000                	unimp
 642:	31000507          	.insn	4, 0x31000507
 646:	00211c13          	slli	s8,sp,0x2
 64a:	0000                	unimp
 64c:	1608                	addi	a0,sp,800
 64e:	0300                	addi	s0,sp,384
 650:	3a0e                	fld	fs4,224(sp)
 652:	0421                	addi	s0,s0,8
 654:	0b390b3b          	.insn	4, 0x0b390b3b
 658:	1349                	addi	t1,t1,-14
 65a:	0000                	unimp
 65c:	1609                	addi	a2,a2,-30
 65e:	0300                	addi	s0,sp,384
 660:	3a08                	fld	fa0,48(a2)
 662:	0421                	addi	s0,s0,8
 664:	21390b3b          	.insn	4, 0x21390b3b
 668:	491d                	li	s2,7
 66a:	0a000013          	li	zero,160
 66e:	002e                	c.slli	zero,0xb
 670:	213a0e03          	lb	t3,531(s4)
 674:	3b02                	fld	fs6,32(sp)
 676:	0121390b          	.insn	4, 0x0121390b
 67a:	13491927          	.insn	4, 0x13491927
 67e:	2120                	fld	fs0,64(a0)
 680:	0b000003          	lb	zero,176(zero) # b0 <main-0x11ffff50>
 684:	0111                	addi	sp,sp,4
 686:	0e25                	addi	t3,t3,9
 688:	1f030b13          	addi	s6,t1,496
 68c:	01111f1b          	slliw	t5,sp,0x11
 690:	0712                	slli	a4,a4,0x4
 692:	1710                	addi	a2,sp,928
 694:	0000                	unimp
 696:	240c                	fld	fa1,8(s0)
 698:	0b00                	addi	s0,sp,400
 69a:	030b3e0b          	.insn	4, 0x030b3e0b
 69e:	0008                	.insn	2, 0x0008
 6a0:	0d00                	addi	s0,sp,656
 6a2:	012e                	slli	sp,sp,0xb
 6a4:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 6ac:	0b39                	addi	s6,s6,14
 6ae:	13491927          	.insn	4, 0x13491927
 6b2:	0111                	addi	sp,sp,4
 6b4:	0712                	slli	a4,a4,0x4
 6b6:	1840                	addi	s0,sp,52
 6b8:	197a                	slli	s2,s2,0x3e
 6ba:	1301                	addi	t1,t1,-32
 6bc:	0000                	unimp
 6be:	340e                	fld	fs0,224(sp)
 6c0:	0300                	addi	s0,sp,384
 6c2:	3a0e                	fld	fs4,224(sp)
 6c4:	390b3b0b          	.insn	4, 0x390b3b0b
 6c8:	0213490b          	.insn	4, 0x0213490b
 6cc:	0018                	.insn	2, 0x0018
 6ce:	0f00                	addi	s0,sp,912
 6d0:	012e                	slli	sp,sp,0xb
 6d2:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 6da:	0b39                	addi	s6,s6,14
 6dc:	01111927          	.insn	4, 0x01111927
 6e0:	0712                	slli	a4,a4,0x4
 6e2:	1840                	addi	s0,sp,52
 6e4:	197a                	slli	s2,s2,0x3e
 6e6:	1301                	addi	t1,t1,-32
 6e8:	0000                	unimp
 6ea:	2e10                	fld	fa2,24(a2)
 6ec:	3f01                	addiw	t5,t5,-32 # fffffffffffdffe0 <__sheap+0xffffffffedfdcfe0>
 6ee:	0319                	addi	t1,t1,6
 6f0:	3a0e                	fld	fs4,224(sp)
 6f2:	390b3b0b          	.insn	4, 0x390b3b0b
 6f6:	8719270b          	.insn	4, 0x8719270b
 6fa:	1901                	addi	s2,s2,-32
 6fc:	0111                	addi	sp,sp,4
 6fe:	0712                	slli	a4,a4,0x4
 700:	1840                	addi	s0,sp,52
 702:	197a                	slli	s2,s2,0x3e
 704:	1301                	addi	t1,t1,-32
 706:	0000                	unimp
 708:	1d11                	addi	s10,s10,-28 # fffffffffffdffe4 <__sheap+0xffffffffedfdcfe4>
 70a:	3101                	addiw	sp,sp,-32
 70c:	b8015213          	.insn	4, 0xb8015213
 710:	0b42                	slli	s6,s6,0x10
 712:	0111                	addi	sp,sp,4
 714:	0712                	slli	a4,a4,0x4
 716:	0b58                	addi	a4,sp,404
 718:	0b59                	addi	s6,s6,22
 71a:	13010b57          	.insn	4, 0x13010b57
 71e:	0000                	unimp
 720:	2e12                	fld	ft8,256(sp)
 722:	0301                	addi	t1,t1,0
 724:	3a0e                	fld	fs4,224(sp)
 726:	390b3b0b          	.insn	4, 0x390b3b0b
 72a:	4919270b          	.insn	4, 0x4919270b
 72e:	010b2013          	slti	zero,s6,16
 732:	13000013          	li	zero,304
 736:	0005                	c.nop	1
 738:	0b3a0803          	lb	a6,179(s4)
 73c:	0b390b3b          	.insn	4, 0x0b390b3b
 740:	1349                	addi	t1,t1,-14
 742:	0000                	unimp
 744:	2e14                	fld	fa3,24(a2)
 746:	0301                	addi	t1,t1,0
 748:	3a0e                	fld	fs4,224(sp)
 74a:	390b3b0b          	.insn	4, 0x390b3b0b
 74e:	4919270b          	.insn	4, 0x4919270b
 752:	000b2013          	slti	zero,s6,0
 756:	0000                	unimp
 758:	2401                	sext.w	s0,s0
 75a:	0b00                	addi	s0,sp,400
 75c:	030b3e0b          	.insn	4, 0x030b3e0b
 760:	000e                	c.slli	zero,0x3
 762:	0200                	addi	s0,sp,256
 764:	0005                	c.nop	1
 766:	1349                	addi	t1,t1,-14
 768:	0000                	unimp
 76a:	0b000f03          	lb	t5,176(zero) # b0 <main-0x11ffff50>
 76e:	0821                	addi	a6,a6,8
 770:	1349                	addi	t1,t1,-14
 772:	0000                	unimp
 774:	4904                	lw	s1,16(a0)
 776:	0200                	addi	s0,sp,256
 778:	7e18                	ld	a4,56(a2)
 77a:	0018                	.insn	2, 0x0018
 77c:	0500                	addi	s0,sp,640
 77e:	0111                	addi	sp,sp,4
 780:	0e25                	addi	t3,t3,9
 782:	1f030b13          	addi	s6,t1,496
 786:	01111f1b          	slliw	t5,sp,0x11
 78a:	0712                	slli	a4,a4,0x4
 78c:	1710                	addi	a2,sp,928
 78e:	0000                	unimp
 790:	2406                	fld	fs0,64(sp)
 792:	0b00                	addi	s0,sp,400
 794:	030b3e0b          	.insn	4, 0x030b3e0b
 798:	0008                	.insn	2, 0x0008
 79a:	0700                	addi	s0,sp,896
 79c:	0016                	c.slli	zero,0x5
 79e:	0b3a0803          	lb	a6,179(s4)
 7a2:	0b390b3b          	.insn	4, 0x0b390b3b
 7a6:	1349                	addi	t1,t1,-14
 7a8:	0000                	unimp
 7aa:	1608                	addi	a0,sp,800
 7ac:	0300                	addi	s0,sp,384
 7ae:	3a0e                	fld	fs4,224(sp)
 7b0:	390b3b0b          	.insn	4, 0x390b3b0b
 7b4:	0013490b          	.insn	4, 0x0013490b
 7b8:	0900                	addi	s0,sp,144
 7ba:	002e                	c.slli	zero,0xb
 7bc:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 7c4:	0b39                	addi	s6,s6,14
 7c6:	01871927          	.insn	4, 0x01871927
 7ca:	3c19                	addiw	s8,s8,-26
 7cc:	0019                	c.nop	6
 7ce:	0a00                	addi	s0,sp,272
 7d0:	012e                	slli	sp,sp,0xb
 7d2:	0e03193f 0b3b0b3a 	.insn	8, 0x0b3b0b3a0e03193f
 7da:	0b39                	addi	s6,s6,14
 7dc:	13491927          	.insn	4, 0x13491927
 7e0:	193c                	addi	a5,sp,184
 7e2:	1301                	addi	t1,t1,-32
 7e4:	0000                	unimp
 7e6:	3f012e0b          	.insn	4, 0x3f012e0b
 7ea:	0319                	addi	t1,t1,6
 7ec:	3a0e                	fld	fs4,224(sp)
 7ee:	390b3b0b          	.insn	4, 0x390b3b0b
 7f2:	1119270b          	.insn	4, 0x1119270b
 7f6:	1201                	addi	tp,tp,-32 # ffffffffffffffe0 <__sheap+0xffffffffedffcfe0>
 7f8:	7a184007          	.insn	4, 0x7a184007
 7fc:	0019                	c.nop	6
 7fe:	0c00                	addi	s0,sp,528
 800:	0148                	addi	a0,sp,132
 802:	017d                	addi	sp,sp,31
 804:	1301137f 480d0000 	.insn	12, 0x7f017d00480d00001301137f
 80c:	7f017d00 
 810:	00000013          	nop
 814:	1101                	addi	sp,sp,-32
 816:	1000                	addi	s0,sp,32
 818:	12011117          	auipc	sp,0x12011
 81c:	1b0e030f          	.insn	4, 0x1b0e030f
 820:	250e                	fld	fa0,192(sp)
 822:	130e                	slli	t1,t1,0x23
 824:	0005                	c.nop	1
 826:	0000                	unimp
 828:	0501                	addi	a0,a0,0
 82a:	0300                	addi	s0,sp,384
 82c:	3a08                	fld	fa0,48(a2)
 82e:	0121                	addi	sp,sp,8 # 12011820 <__sheap+0xe820>
 830:	0b390b3b          	.insn	4, 0x0b390b3b
 834:	1349                	addi	t1,t1,-14
 836:	1702                	slli	a4,a4,0x20
 838:	001742b7          	lui	t0,0x174
 83c:	0200                	addi	s0,sp,256
 83e:	0034                	addi	a3,sp,8
 840:	213a0803          	lb	a6,531(s4)
 844:	3b01                	addiw	s6,s6,-32
 846:	490b390b          	.insn	4, 0x490b390b
 84a:	b7170213          	addi	tp,a4,-1167
 84e:	1742                	slli	a4,a4,0x30
 850:	0000                	unimp
 852:	0b002403          	lw	s0,176(zero) # b0 <main-0x11ffff50>
 856:	030b3e0b          	.insn	4, 0x030b3e0b
 85a:	000e                	c.slli	zero,0x3
 85c:	0400                	addi	s0,sp,512
 85e:	012e                	slli	sp,sp,0xb
 860:	0e03193f 3b01213a 	.insn	8, 0x3b01213a0e03193f
 868:	0121390b          	.insn	4, 0x0121390b
 86c:	13491927          	.insn	4, 0x13491927
 870:	0111                	addi	sp,sp,4
 872:	0712                	slli	a4,a4,0x4
 874:	1840                	addi	s0,sp,52
 876:	197a                	slli	s2,s2,0x3e
 878:	1301                	addi	t1,t1,-32
 87a:	0000                	unimp
 87c:	0f05                	addi	t5,t5,1
 87e:	0b00                	addi	s0,sp,400
 880:	0821                	addi	a6,a6,8
 882:	1349                	addi	t1,t1,-14
 884:	0000                	unimp
 886:	0506                	slli	a0,a0,0x1
 888:	0300                	addi	s0,sp,384
 88a:	3a0e                	fld	fs4,224(sp)
 88c:	0121                	addi	sp,sp,8
 88e:	0b390b3b          	.insn	4, 0x0b390b3b
 892:	1349                	addi	t1,t1,-14
 894:	1802                	slli	a6,a6,0x20
 896:	0000                	unimp
 898:	03001607          	.insn	4, 0x03001607
 89c:	3a08                	fld	fa0,48(a2)
 89e:	0221                	addi	tp,tp,8 # 8 <main-0x11fffff8>
 8a0:	21390b3b          	.insn	4, 0x21390b3b
 8a4:	491d                	li	s2,7
 8a6:	08000013          	li	zero,128
 8aa:	0005                	c.nop	1
 8ac:	213a0803          	lb	a6,531(s4)
 8b0:	3b01                	addiw	s6,s6,-32
 8b2:	490b390b          	.insn	4, 0x490b390b
 8b6:	00180213          	addi	tp,a6,1
 8ba:	0900                	addi	s0,sp,144
 8bc:	0026                	c.slli	zero,0x9
 8be:	1349                	addi	t1,t1,-14
 8c0:	0000                	unimp
 8c2:	160a                	slli	a2,a2,0x22
 8c4:	0300                	addi	s0,sp,384
 8c6:	3a0e                	fld	fs4,224(sp)
 8c8:	0221                	addi	tp,tp,8 # 8 <main-0x11fffff8>
 8ca:	21390b3b          	.insn	4, 0x21390b3b
 8ce:	490d                	li	s2,3
 8d0:	0b000013          	li	zero,176
 8d4:	0111                	addi	sp,sp,4
 8d6:	0e25                	addi	t3,t3,9
 8d8:	1f030b13          	addi	s6,t1,496
 8dc:	17551f1b          	.insn	4, 0x17551f1b
 8e0:	0111                	addi	sp,sp,4
 8e2:	1710                	addi	a2,sp,928
 8e4:	0000                	unimp
 8e6:	240c                	fld	fa1,8(s0)
 8e8:	0b00                	addi	s0,sp,400
 8ea:	030b3e0b          	.insn	4, 0x030b3e0b
 8ee:	0008                	.insn	2, 0x0008
 8f0:	0d00                	addi	s0,sp,656
 8f2:	0111010b          	.insn	4, 0x0111010b
 8f6:	0712                	slli	a4,a4,0x4
 8f8:	0000                	unimp
 8fa:	260e                	fld	fa2,192(sp)
 8fc:	0000                	unimp
 8fe:	0f00                	addi	s0,sp,912
 900:	0b0b000f          	.insn	4, 0x0b0b000f
 904:	0000                	unimp
 906:	2e10                	fld	fa2,24(a2)
 908:	3f01                	addiw	t5,t5,-32
 90a:	0319                	addi	t1,t1,6
 90c:	3a0e                	fld	fs4,224(sp)
 90e:	390b3b0b          	.insn	4, 0x390b3b0b
 912:	4919270b          	.insn	4, 0x4919270b
 916:	12011113          	.insn	4, 0x12011113
 91a:	7a184007          	.insn	4, 0x7a184007
 91e:	0019                	c.nop	6
	...

Disassembly of section .debug_loclists:

0000000000000000 <.debug_loclists>:
   0:	003e                	c.slli	zero,0xf
   2:	0000                	unimp
   4:	0005                	c.nop	1
   6:	0008                	.insn	2, 0x0008
   8:	0000                	unimp
   a:	0000                	unimp
   c:	0400                	addi	s0,sp,512
   e:	0004                	.insn	2, 0x0004
  10:	0006                	c.slli	zero,0x1
  12:	0000                	unimp
  14:	0012                	c.slli	zero,0x4
  16:	0000                	unimp
  18:	0400                	addi	s0,sp,512
  1a:	0a00                	addi	s0,sp,272
  1c:	5a01                	li	s4,-32
  1e:	0a04                	addi	s1,sp,272
  20:	0440                	addi	s0,sp,516
  22:	9f5a01a3          	sb	s5,-1565(s4)
  26:	0000                	unimp
  28:	0606                	slli	a2,a2,0x1
  2a:	0600                	addi	s0,sp,768
  2c:	0000                	unimp
  2e:	1200                	addi	s0,sp,288
  30:	0000                	unimp
  32:	0000                	unimp
  34:	0004                	.insn	2, 0x0004
  36:	011d                	addi	sp,sp,7
  38:	401d045b          	.insn	4, 0x401d045b
  3c:	a304                	fsd	fs1,0(a4)
  3e:	5b01                	li	s6,-32
  40:	009f 0770 0000      	.insn	6, 0x0770009f
  46:	0005                	c.nop	1
  48:	0008                	.insn	2, 0x0008
  4a:	0000                	unimp
  4c:	0000                	unimp
  4e:	0c00                	addi	s0,sp,528
  50:	000c                	.insn	2, 0x000c
  52:	d204                	sw	s1,32(a2)
  54:	f30a                	sd	sp,416(sp)
  56:	010a                	slli	sp,sp,0x2
  58:	045a                	slli	s0,s0,0x16
  5a:	0afa0af3          	.insn	4, 0x0afa0af3
  5e:	a304                	fsd	fs1,0(a4)
  60:	5a01                	li	s4,-32
  62:	009f 000c f404      	.insn	6, 0xf404000c009f
  68:	fa0a                	sd	sp,304(sp)
  6a:	010a                	slli	sp,sp,0x2
  6c:	005a                	c.slli	zero,0x16
  6e:	0700                	addi	s0,sp,896
  70:	25242407          	flw	fs0,594(s0)
  74:	a825                	j	ac <main-0x11ffff54>
  76:	a801                	j	86 <main-0x11ffff7a>
  78:	a901                	j	488 <main-0x11fffb78>
  7a:	a901                	j	48a <main-0x11fffb76>
  7c:	0001                	nop
  7e:	8e04                	.insn	2, 0x8e04
  80:	9e05                	subw	a2,a2,s1
  82:	0105                	addi	sp,sp,1
  84:	045a                	slli	s0,s0,0x16
  86:	059e                	slli	a1,a1,0x7
  88:	06a6                	slli	a3,a3,0x9
  8a:	5901                	li	s2,-32
  8c:	a604                	fsd	fs1,8(a2)
  8e:	ac06                	fsd	ft1,24(sp)
  90:	0406                	slli	s0,s0,0x1
  92:	9f5a01a3          	sb	s5,-1565(s4)
  96:	ac04                	fsd	fs1,24(s0)
  98:	b606                	fsd	ft1,296(sp)
  9a:	0109                	addi	sp,sp,2
  9c:	0459                	addi	s0,s0,22
  9e:	09b6                	slli	s3,s3,0xd
  a0:	09bc                	addi	a5,sp,216
  a2:	a304                	fsd	fs1,0(a4)
  a4:	5a01                	li	s4,-32
  a6:	049f 09bc 0ad2      	.insn	6, 0x0ad209bc049f
  ac:	5901                	li	s2,-32
  ae:	0000                	unimp
  b0:	0c0c                	addi	a1,sp,528
  b2:	2828251b          	.insn	4, 0x2828251b
  b6:	45452b2b          	.insn	4, 0x45452b2b
  ba:	5656                	lw	a2,116(sp)
  bc:	5c5c                	lw	a5,60(s0)
  be:	5f5f 7171 7575      	.insn	6, 0x757571715f5f
  c4:	7f7f7b7b          	.insn	4, 0x7f7f7b7b
  c8:	0185                	addi	gp,gp,1
  ca:	0185                	addi	gp,gp,1
  cc:	0188                	addi	a0,sp,192
  ce:	0188                	addi	a0,sp,192
  d0:	019d                	addi	gp,gp,7
  d2:	01a9                	addi	gp,gp,10
  d4:	01aa                	slli	gp,gp,0xa
  d6:	01aa                	slli	gp,gp,0xa
  d8:	01ad                	addi	gp,gp,11
  da:	01ad                	addi	gp,gp,11
  dc:	01af01af          	.insn	4, 0x01af01af
  e0:	01b1                	addi	gp,gp,12
  e2:	01b1                	addi	gp,gp,12
  e4:	01b2                	slli	gp,gp,0xc
  e6:	01b2                	slli	gp,gp,0xc
  e8:	01b5                	addi	gp,gp,13
  ea:	01b5                	addi	gp,gp,13
  ec:	01b8                	addi	a4,sp,200
  ee:	01b8                	addi	a4,sp,200
  f0:	01bb01bb          	addw	gp,s6,s11
  f4:	01be                	slli	gp,gp,0xf
  f6:	01be                	slli	gp,gp,0xf
  f8:	01c1                	addi	gp,gp,16
  fa:	01c1                	addi	gp,gp,16
  fc:	0400                	addi	s0,sp,512
  fe:	058e                	slli	a1,a1,0x3
 100:	05ca                	slli	a1,a1,0x12
 102:	5b01                	li	s6,-32
 104:	ca04                	sw	s1,16(a2)
 106:	8c05                	sub	s0,s0,s1
 108:	0106                	slli	sp,sp,0x1
 10a:	0462                	slli	s0,s0,0x18
 10c:	06ac                	addi	a1,sp,840
 10e:	06c0                	addi	s0,sp,836
 110:	6201                	.insn	2, 0x6201
 112:	c004                	sw	s1,0(s0)
 114:	d406                	sw	ra,40(sp)
 116:	0306                	slli	t1,t1,0x1
 118:	0882                	c.slli64	a7
 11a:	049f 06d4 0790      	.insn	6, 0x079006d4049f
 120:	6201                	.insn	2, 0x6201
 122:	9004                	.insn	2, 0x9004
 124:	0307c007          	.insn	4, 0x0307c007
 128:	0882                	c.slli64	a7
 12a:	049f 07c0 07c6      	.insn	6, 0x07c607c0049f
 130:	6201                	.insn	2, 0x6201
 132:	c604                	sw	s1,8(a2)
 134:	0307da07          	.insn	4, 0x0307da07
 138:	0882                	c.slli64	a7
 13a:	049f 07da 089c      	.insn	6, 0x089c07da049f
 140:	6201                	.insn	2, 0x6201
 142:	9c04                	.insn	2, 0x9c04
 144:	b008                	fsd	fa0,32(s0)
 146:	0308                	addi	a0,sp,384
 148:	0882                	c.slli64	a7
 14a:	049f 08b0 08b6      	.insn	6, 0x08b608b0049f
 150:	6201                	.insn	2, 0x6201
 152:	b604                	fsd	fs1,40(a2)
 154:	be08                	fsd	fa0,56(a2)
 156:	0308                	addi	a0,sp,384
 158:	0882                	c.slli64	a7
 15a:	049f 08be 08ca      	.insn	6, 0x08ca08be049f
 160:	6201                	.insn	2, 0x6201
 162:	ca04                	sw	s1,16(a2)
 164:	de08                	sw	a0,56(a2)
 166:	0308                	addi	a0,sp,384
 168:	0882                	c.slli64	a7
 16a:	049f 08de 0990      	.insn	6, 0x099008de049f
 170:	6201                	.insn	2, 0x6201
 172:	bc04                	fsd	fs1,56(s0)
 174:	bc09                	j	fffffffffffffb86 <__sheap+0xffffffffedffcb86>
 176:	0109                	addi	sp,sp,2
 178:	0462                	slli	s0,s0,0x18
 17a:	09bc                	addi	a5,sp,216
 17c:	09d0                	addi	a2,sp,212
 17e:	9f088203          	lb	tp,-1552(a7)
 182:	d004                	sw	s1,32(s0)
 184:	d409                	beqz	s0,8e <main-0x11ffff72>
 186:	0109                	addi	sp,sp,2
 188:	0462                	slli	s0,s0,0x18
 18a:	09d4                	addi	a3,sp,212
 18c:	09e0                	addi	s0,sp,220
 18e:	5b01                	li	s6,-32
 190:	e004                	sd	s1,0(s0)
 192:	e009                	bnez	s0,194 <main-0x11fffe6c>
 194:	0109                	addi	sp,sp,2
 196:	0462                	slli	s0,s0,0x18
 198:	09e0                	addi	s0,sp,220
 19a:	09f4                	addi	a3,sp,220
 19c:	9f088203          	lb	tp,-1552(a7)
 1a0:	f404                	sd	s1,40(s0)
 1a2:	f809                	bnez	s0,b4 <main-0x11ffff4c>
 1a4:	0109                	addi	sp,sp,2
 1a6:	0462                	slli	s0,s0,0x18
 1a8:	09f8                	addi	a4,sp,220
 1aa:	0a8c                	addi	a1,sp,336
 1ac:	9f088203          	lb	tp,-1552(a7)
 1b0:	8c04                	.insn	2, 0x8c04
 1b2:	900a                	c.add	zero,sp
 1b4:	010a                	slli	sp,sp,0x2
 1b6:	0462                	slli	s0,s0,0x18
 1b8:	0a90                	addi	a2,sp,336
 1ba:	0aa4                	addi	s1,sp,344
 1bc:	9f088203          	lb	tp,-1552(a7)
 1c0:	a404                	fsd	fs1,8(s0)
 1c2:	d20a                	sw	sp,36(sp)
 1c4:	010a                	slli	sp,sp,0x2
 1c6:	0062                	c.slli	zero,0x18
 1c8:	0c04                	addi	s1,sp,528
 1ca:	1c0c                	addi	a1,sp,560
 1cc:	5125                	li	sp,-23
 1ce:	5551                	li	a0,-12
 1d0:	7e55                	lui	t3,0xffff5
 1d2:	807e                	c.mv	zero,t6
 1d4:	8001                	c.srli64	s0
 1d6:	9701                	srai	a4,a4,0x20
 1d8:	9701                	srai	a4,a4,0x20
 1da:	9b01                	andi	a4,a4,-32
 1dc:	9b01                	andi	a4,a4,-32
 1de:	9d01                	subw	a0,a0,s0
 1e0:	a901                	j	5f0 <main-0x11fffa10>
 1e2:	af01                	j	8f2 <main-0x11fff70e>
 1e4:	af01                	j	8f4 <main-0x11fff70c>
 1e6:	b101                	j	fffffffffffffde6 <__sheap+0xffffffffedffcde6>
 1e8:	b101                	j	fffffffffffffde8 <__sheap+0xffffffffedffcde8>
 1ea:	0001                	nop
 1ec:	8e04                	.insn	2, 0x8e04
 1ee:	ca05                	beqz	a2,21e <main-0x11fffde2>
 1f0:	0205                	addi	tp,tp,1 # 1 <main-0x11ffffff>
 1f2:	9f30                	.insn	2, 0x9f30
 1f4:	ca04                	sw	s1,16(a2)
 1f6:	9605                	srai	a2,a2,0x21
 1f8:	0106                	slli	sp,sp,0x1
 1fa:	0458                	addi	a4,sp,516
 1fc:	06ac                	addi	a1,sp,840
 1fe:	07ac                	addi	a1,sp,968
 200:	5801                	li	a6,-32
 202:	ac04                	fsd	fs1,24(s0)
 204:	0307be07          	fld	ft8,48(a5)
 208:	0278                	addi	a4,sp,268
 20a:	049f 07be 08bc      	.insn	6, 0x08bc07be049f
 210:	5801                	li	a6,-32
 212:	bc04                	fsd	fs1,56(s0)
 214:	c608                	sw	a0,8(a2)
 216:	0308                	addi	a0,sp,384
 218:	7f78                	ld	a4,248(a4)
 21a:	049f 08c6 0988      	.insn	6, 0x098808c6049f
 220:	5801                	li	a6,-32
 222:	8804                	.insn	2, 0x8804
 224:	8e09                	sub	a2,a2,a0
 226:	0309                	addi	t1,t1,2
 228:	7f78                	ld	a4,248(a4)
 22a:	049f 098e 0990      	.insn	6, 0x0990098e049f
 230:	5801                	li	a6,-32
 232:	bc04                	fsd	fs1,56(s0)
 234:	d409                	beqz	s0,13e <main-0x11fffec2>
 236:	0109                	addi	sp,sp,2
 238:	0458                	addi	a4,sp,516
 23a:	09d4                	addi	a3,sp,212
 23c:	09e0                	addi	s0,sp,220
 23e:	3002                	fld	ft0,32(sp)
 240:	049f 09e0 0ad2      	.insn	6, 0x0ad209e0049f
 246:	5801                	li	a6,-32
 248:	0400                	addi	s0,sp,512
 24a:	0c0c                	addi	a1,sp,528
 24c:	1010                	addi	a2,sp,32
 24e:	251c1313          	.insn	4, 0x251c1313
 252:	6666                	ld	a2,88(sp)
 254:	7070                	ld	a2,224(s0)
 256:	019d                	addi	gp,gp,7
 258:	01a9                	addi	gp,gp,10
 25a:	01af01af          	.insn	4, 0x01af01af
 25e:	01b1                	addi	gp,gp,12
 260:	01b1                	addi	gp,gp,12
 262:	01c301c3          	fmadd.s	ft3,ft6,ft8,ft0,rne
 266:	0400                	addi	s0,sp,512
 268:	058e                	slli	a1,a1,0x3
 26a:	05ca                	slli	a1,a1,0x12
 26c:	3002                	fld	ft0,32(sp)
 26e:	049f 05ca 05d2      	.insn	6, 0x05d205ca049f
 274:	6801                	.insn	2, 0x6801
 276:	d204                	sw	s1,32(a2)
 278:	f405                	bnez	s0,1a0 <main-0x11fffe60>
 27a:	0105                	addi	sp,sp,1
 27c:	0464                	addi	s1,sp,524
 27e:	05f4                	addi	a3,sp,716
 280:	0696                	slli	a3,a3,0x5
 282:	6801                	.insn	2, 0x6801
 284:	ac04                	fsd	fs1,24(s0)
 286:	e206                	sd	ra,256(sp)
 288:	04640107          	.insn	4, 0x04640107
 28c:	07e2                	slli	a5,a5,0x18
 28e:	089c                	addi	a5,sp,80
 290:	6801                	.insn	2, 0x6801
 292:	9c04                	.insn	2, 0x9c04
 294:	9008                	.insn	2, 0x9008
 296:	0109                	addi	sp,sp,2
 298:	0464                	addi	s1,sp,524
 29a:	09bc                	addi	a5,sp,216
 29c:	09d4                	addi	a3,sp,212
 29e:	6801                	.insn	2, 0x6801
 2a0:	d404                	sw	s1,40(s0)
 2a2:	e009                	bnez	s0,2a4 <main-0x11fffd5c>
 2a4:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
 2a6:	9f30                	.insn	2, 0x9f30
 2a8:	e004                	sd	s1,0(s0)
 2aa:	a809                	j	2bc <main-0x11fffd44>
 2ac:	010a                	slli	sp,sp,0x2
 2ae:	0468                	addi	a0,sp,524
 2b0:	0aa8                	addi	a0,sp,344
 2b2:	0ad2                	slli	s5,s5,0x14
 2b4:	6401                	.insn	2, 0x6401
 2b6:	7100                	ld	s0,32(a0)
 2b8:	04747373          	csrrci	t1,0x47,8
 2bc:	089c                	addi	a5,sp,80
 2be:	08a0                	addi	s0,sp,88
 2c0:	9400820b          	.insn	4, 0x9400820b
 2c4:	0804                	addi	s1,sp,16
 2c6:	2420                	fld	fs0,72(s0)
 2c8:	2008                	fld	fa0,0(s0)
 2ca:	9f26                	add	t5,t5,s1
 2cc:	a004                	fsd	fs1,0(s0)
 2ce:	ad08                	fsd	fa0,24(a0)
 2d0:	0108                	addi	a0,sp,128
 2d2:	005a                	c.slli	zero,0x16
 2d4:	3e38                	fld	fa4,120(a2)
 2d6:	01ce                	slli	gp,gp,0x13
 2d8:	0400                	addi	s0,sp,512
 2da:	06f4                	addi	a3,sp,844
 2dc:	0788                	addi	a0,sp,960
 2de:	6801                	.insn	2, 0x6801
 2e0:	c604                	sw	s1,8(a2)
 2e2:	d20a                	sw	sp,36(sp)
 2e4:	020a                	slli	tp,tp,0x2
 2e6:	9f30                	.insn	2, 0x9f30
 2e8:	7b00                	ld	s0,48(a4)
 2ea:	7f7f                	.insn	2, 0x7f7f
 2ec:	0180                	addi	s0,sp,192
 2ee:	b604                	fsd	fs1,40(a2)
 2f0:	be08                	fsd	fa0,56(a2)
 2f2:	0208                	addi	a0,sp,256
 2f4:	0082                	c.slli64	ra
 2f6:	be04                	fsd	fs1,56(a2)
 2f8:	c508                	sw	a0,8(a0)
 2fa:	0208                	addi	a0,sp,256
 2fc:	7882                	ld	a7,32(sp)
 2fe:	4800                	lw	s0,16(s0)
 300:	0451                	addi	s0,s0,20
 302:	0798                	addi	a4,sp,960
 304:	07ac                	addi	a1,sp,968
 306:	a006                	fsd	ft1,0(sp)
 308:	0aac                	addi	a1,sp,344
 30a:	0000                	unimp
 30c:	0000                	unimp
 30e:	4d4a                	lw	s10,144(sp)
 310:	514d                	li	sp,-13
 312:	9804                	.insn	2, 0x9804
 314:	0207a007          	flw	ft0,32(a5)
 318:	9f30                	.insn	2, 0x9f30
 31a:	a004                	fsd	fs1,0(s0)
 31c:	0207ac07          	flw	fs8,32(a5)
 320:	9f31                	addw	a4,a4,a2
 322:	8e00                	.insn	2, 0x8e00
 324:	9b01                	andi	a4,a4,-32
 326:	c301                	beqz	a4,326 <main-0x11fffcda>
 328:	ce01                	beqz	a2,340 <main-0x11fffcc0>
 32a:	0401                	addi	s0,s0,0
 32c:	08e4                	addi	s1,sp,92
 32e:	098e                	slli	s3,s3,0x3
 330:	9f250803          	lb	a6,-1550(a0)
 334:	a804                	fsd	fs1,16(s0)
 336:	c60a                	sw	sp,12(sp)
 338:	030a                	slli	t1,t1,0x2
 33a:	2508                	fld	fa0,8(a0)
 33c:	009f 01c6 01c9      	.insn	6, 0x01c901c6009f
 342:	01c9                	addi	gp,gp,18
 344:	01cc                	addi	a1,sp,196
 346:	a804                	fsd	fs1,16(s0)
 348:	b20a                	fsd	ft2,288(sp)
 34a:	010a                	slli	sp,sp,0x2
 34c:	045f 0ab2 0abf      	.insn	6, 0x0abf0ab2045f
 352:	0309                	addi	t1,t1,2
 354:	2108                	fld	fa0,0(a0)
 356:	1200                	addi	s0,sp,288
 358:	0000                	unimp
 35a:	0000                	unimp
 35c:	2100                	fld	fs0,0(a0)
 35e:	9d25                	addw	a0,a0,s1
 360:	a001                	j	360 <main-0x11fffca0>
 362:	a001                	j	362 <main-0x11fffc9e>
 364:	a201                	j	464 <main-0x11fffb9c>
 366:	0401                	addi	s0,s0,0
 368:	069a                	slli	a3,a3,0x6
 36a:	06ac                	addi	a1,sp,840
 36c:	5f01                	li	t5,-32
 36e:	9004                	.insn	2, 0x9004
 370:	9a09                	andi	a2,a2,-30
 372:	0109                	addi	sp,sp,2
 374:	045f 099a 09a5      	.insn	6, 0x09a5099a045f
 37a:	0309                	addi	t1,t1,2
 37c:	2108                	fld	fa0,0(a0)
 37e:	1200                	addi	s0,sp,288
 380:	0000                	unimp
 382:	0000                	unimp
 384:	0000                	unimp
 386:	1414                	addi	a3,sp,544
 388:	76767373          	csrrci	t1,0x767,12
 38c:	018d                	addi	gp,gp,3
 38e:	018d                	addi	gp,gp,3
 390:	0195                	addi	gp,gp,5
 392:	0195                	addi	gp,gp,5
 394:	01aa                	slli	gp,gp,0xa
 396:	01aa                	slli	gp,gp,0xa
 398:	01b301b3          	add	gp,t1,s11
 39c:	0400                	addi	s0,sp,512
 39e:	0182                	c.slli64	gp
 3a0:	01c0                	addi	s0,sp,196
 3a2:	5a01                	li	s4,-32
 3a4:	c004                	sw	s1,0(s0)
 3a6:	b801                	j	fffffffffffffbb6 <__sheap+0xffffffffedffcbb6>
 3a8:	01a30403          	lb	s0,26(t1)
 3ac:	9f5a                	add	t5,t5,s6
 3ae:	b804                	fsd	fs1,48(s0)
 3b0:	0103c603          	lbu	a2,16(t2)
 3b4:	045a                	slli	s0,s0,0x16
 3b6:	03c6                	slli	t2,t2,0x11
 3b8:	0488                	addi	a0,sp,576
 3ba:	a304                	fsd	fs1,0(a4)
 3bc:	5a01                	li	s4,-32
 3be:	049f 0488 04a4      	.insn	6, 0x04a40488049f
 3c4:	5a01                	li	s4,-32
 3c6:	a404                	fsd	fs1,8(s0)
 3c8:	ec04                	sd	s1,24(s0)
 3ca:	0404                	addi	s1,sp,512
 3cc:	9f5a01a3          	sb	s5,-1565(s4)
 3d0:	ec04                	sd	s1,24(s0)
 3d2:	f804                	sd	s1,48(s0)
 3d4:	0104                	addi	s1,sp,128
 3d6:	045a                	slli	s0,s0,0x16
 3d8:	04f8                	addi	a4,sp,588
 3da:	058e                	slli	a1,a1,0x3
 3dc:	a304                	fsd	fs1,0(a4)
 3de:	5a01                	li	s4,-32
 3e0:	009f 2500 7325      	.insn	6, 0x73252500009f
 3e6:	8d797973          	csrrci	s2,0x8d7,18
 3ea:	8d01                	sub	a0,a0,s0
 3ec:	9501                	srai	a0,a0,0x20
 3ee:	9501                	srai	a0,a0,0x20
 3f0:	aa01                	j	500 <main-0x11fffb00>
 3f2:	aa01                	j	502 <main-0x11fffafe>
 3f4:	b501                	j	1f4 <main-0x11fffe0c>
 3f6:	b501                	j	1f6 <main-0x11fffe0a>
 3f8:	0001                	nop
 3fa:	8204                	.insn	2, 0x8204
 3fc:	f401                	bnez	s0,304 <main-0x11fffcfc>
 3fe:	0101                	addi	sp,sp,0
 400:	01f4045b          	.insn	4, 0x01f4045b
 404:	03b8                	addi	a4,sp,456
 406:	a304                	fsd	fs1,0(a4)
 408:	5b01                	li	s6,-32
 40a:	049f 03b8 03d2      	.insn	6, 0x03d203b8049f
 410:	5b01                	li	s6,-32
 412:	d204                	sw	s1,32(a2)
 414:	04048803          	lb	a6,64(s1)
 418:	9f5b01a3          	sb	s5,-1565(s6)
 41c:	8804                	.insn	2, 0x8804
 41e:	a404                	fsd	fs1,8(s0)
 420:	0104                	addi	s1,sp,128
 422:	04a4045b          	.insn	4, 0x04a4045b
 426:	04ec                	addi	a1,sp,588
 428:	a304                	fsd	fs1,0(a4)
 42a:	5b01                	li	s6,-32
 42c:	049f 04ec 0585      	.insn	6, 0x058504ec049f
 432:	5b01                	li	s6,-32
 434:	8504                	.insn	2, 0x8504
 436:	8e05                	sub	a2,a2,s1
 438:	0405                	addi	s0,s0,1
 43a:	9f5b01a3          	sb	s5,-1565(s6)
 43e:	0000                	unimp
 440:	1414                	addi	a3,sp,544
 442:	76767373          	csrrci	t1,0x767,12
 446:	018d                	addi	gp,gp,3
 448:	018d                	addi	gp,gp,3
 44a:	0195                	addi	gp,gp,5
 44c:	0195                	addi	gp,gp,5
 44e:	01aa                	slli	gp,gp,0xa
 450:	01aa                	slli	gp,gp,0xa
 452:	01b1                	addi	gp,gp,12
 454:	01b1                	addi	gp,gp,12
 456:	0400                	addi	s0,sp,512
 458:	0182                	c.slli64	gp
 45a:	01c0                	addi	s0,sp,196
 45c:	5c01                	li	s8,-32
 45e:	c004                	sw	s1,0(s0)
 460:	b801                	j	fffffffffffffc70 <__sheap+0xffffffffedffcc70>
 462:	01a30403          	lb	s0,26(t1)
 466:	9f5c                	.insn	2, 0x9f5c
 468:	b804                	fsd	fs1,48(s0)
 46a:	0103c603          	lbu	a2,16(t2)
 46e:	045c                	addi	a5,sp,516
 470:	03c6                	slli	t2,t2,0x11
 472:	0488                	addi	a0,sp,576
 474:	a304                	fsd	fs1,0(a4)
 476:	5c01                	li	s8,-32
 478:	049f 0488 04a4      	.insn	6, 0x04a40488049f
 47e:	5c01                	li	s8,-32
 480:	a404                	fsd	fs1,8(s0)
 482:	ec04                	sd	s1,24(s0)
 484:	0404                	addi	s1,sp,512
 486:	9f5c01a3          	sb	s5,-1565(s8)
 48a:	ec04                	sd	s1,24(s0)
 48c:	f404                	sd	s1,40(s0)
 48e:	0104                	addi	s1,sp,128
 490:	045c                	addi	a5,sp,516
 492:	04f4                	addi	a3,sp,588
 494:	058e                	slli	a1,a1,0x3
 496:	a304                	fsd	fs1,0(a4)
 498:	5c01                	li	s8,-32
 49a:	009f 2700 7327      	.insn	6, 0x73272700009f
 4a0:	83018373          	.insn	4, 0x83018373
 4a4:	8d01                	sub	a0,a0,s0
 4a6:	8d01                	sub	a0,a0,s0
 4a8:	9401                	srai	s0,s0,0x20
 4aa:	9401                	srai	s0,s0,0x20
 4ac:	9e01                	subw	a2,a2,s0
 4ae:	9e01                	subw	a2,a2,s0
 4b0:	a801                	j	4c0 <main-0x11fffb40>
 4b2:	a801                	j	4c2 <main-0x11fffb3e>
 4b4:	aa01                	j	5c4 <main-0x11fffa3c>
 4b6:	aa01                	j	5c6 <main-0x11fffa3a>
 4b8:	b501                	j	2b8 <main-0x11fffd48>
 4ba:	b501                	j	2ba <main-0x11fffd46>
 4bc:	0001                	nop
 4be:	8204                	.insn	2, 0x8204
 4c0:	8001                	c.srli64	s0
 4c2:	0102                	c.slli64	sp
 4c4:	045d                	addi	s0,s0,23
 4c6:	0280                	addi	s0,sp,320
 4c8:	03b8                	addi	a4,sp,456
 4ca:	a304                	fsd	fs1,0(a4)
 4cc:	5d01                	li	s10,-32
 4ce:	049f 03b8 03ec      	.insn	6, 0x03ec03b8049f
 4d4:	5d01                	li	s10,-32
 4d6:	ec04                	sd	s1,24(s0)
 4d8:	04048803          	lb	a6,64(s1)
 4dc:	9f5d01a3          	sb	s5,-1565(s10)
 4e0:	8804                	.insn	2, 0x8804
 4e2:	9c04                	.insn	2, 0x9c04
 4e4:	0104                	addi	s1,sp,128
 4e6:	045d                	addi	s0,s0,23
 4e8:	049c                	addi	a5,sp,576
 4ea:	04be                	slli	s1,s1,0xf
 4ec:	a304                	fsd	fs1,0(a4)
 4ee:	5d01                	li	s10,-32
 4f0:	049f 04be 04dd      	.insn	6, 0x04dd04be049f
 4f6:	5d01                	li	s10,-32
 4f8:	dd04                	sw	s1,56(a0)
 4fa:	ec04                	sd	s1,24(s0)
 4fc:	0404                	addi	s1,sp,512
 4fe:	9f5d01a3          	sb	s5,-1565(s10)
 502:	ec04                	sd	s1,24(s0)
 504:	8504                	.insn	2, 0x8504
 506:	0105                	addi	sp,sp,1
 508:	045d                	addi	s0,s0,23
 50a:	0585                	addi	a1,a1,1
 50c:	058e                	slli	a1,a1,0x3
 50e:	a304                	fsd	fs1,0(a4)
 510:	5d01                	li	s10,-32
 512:	009f 1b0c 1d1b      	.insn	6, 0x1d1b1b0c009f
 518:	231d                	addiw	t1,t1,7
 51a:	76742523          	sw	t2,1898(s0)
 51e:	7776                	ld	a4,376(sp)
 520:	018d7a77          	.insn	4, 0x018d7a77
 524:	0195                	addi	gp,gp,5
 526:	0195                	addi	gp,gp,5
 528:	019e                	slli	gp,gp,0x7
 52a:	01aa                	slli	gp,gp,0xa
 52c:	01b301b3          	add	gp,t1,s11
 530:	0400                	addi	s0,sp,512
 532:	019c                	addi	a5,sp,192
 534:	01d8                	addi	a4,sp,196
 536:	5f01                	li	t5,-32
 538:	d804                	sw	s1,48(s0)
 53a:	dc01                	beqz	s0,452 <main-0x11fffbae>
 53c:	0101                	addi	sp,sp,0
 53e:	045c                	addi	a5,sp,516
 540:	01dc                	addi	a5,sp,196
 542:	01e8                	addi	a0,sp,204
 544:	5f01                	li	t5,-32
 546:	e804                	sd	s1,16(s0)
 548:	f401                	bnez	s0,450 <main-0x11fffbb0>
 54a:	0c01                	addi	s8,s8,0
 54c:	007c                	addi	a5,sp,12
 54e:	2ea8                	fld	fa0,88(a3)
 550:	2ea8007b          	.insn	4, 0x2ea8007b
 554:	9f00a81b          	.insn	4, 0x9f00a81b
 558:	b804                	fsd	fs1,48(s0)
 55a:	0103c603          	lbu	a2,16(t2)
 55e:	045a                	slli	s0,s0,0x16
 560:	03c6                	slli	t2,t2,0x11
 562:	03ca                	slli	t2,t2,0x12
 564:	7c0c                	ld	a1,56(s0)
 566:	a800                	fsd	fs0,16(s0)
 568:	7b2e                	ld	s6,232(sp)
 56a:	a800                	fsd	fs0,16(s0)
 56c:	1b2e                	slli	s6,s6,0x2b
 56e:	00a8                	addi	a0,sp,72
 570:	049f 03ca 03d4      	.insn	6, 0x03d403ca049f
 576:	5f01                	li	t5,-32
 578:	8804                	.insn	2, 0x8804
 57a:	a404                	fsd	fs1,8(s0)
 57c:	0104                	addi	s1,sp,128
 57e:	045a                	slli	s0,s0,0x16
 580:	04a4                	addi	s1,sp,584
 582:	04be                	slli	s1,s1,0xf
 584:	a304                	fsd	fs1,0(a4)
 586:	5a01                	li	s4,-32
 588:	049f 04ec 04f8      	.insn	6, 0x04f804ec049f
 58e:	5a01                	li	s4,-32
 590:	f804                	sd	s1,48(s0)
 592:	8e04                	.insn	2, 0x8e04
 594:	0405                	addi	s0,s0,1
 596:	9f5a01a3          	sb	s5,-1565(s4)
 59a:	0500                	addi	s0,sp,640
 59c:	0a0a                	slli	s4,s4,0x2
 59e:	730e                	ld	t1,224(sp)
 5a0:	8d76                	mv	s10,t4
 5a2:	9e01                	subw	a2,a2,s0
 5a4:	aa01                	j	6b4 <main-0x11fff94c>
 5a6:	0001                	nop
 5a8:	8204                	.insn	2, 0x8204
 5aa:	9801                	andi	s0,s0,-32
 5ac:	0201                	addi	tp,tp,0 # 0 <main-0x12000000>
 5ae:	9f30                	.insn	2, 0x9f30
 5b0:	9804                	.insn	2, 0x9804
 5b2:	a001                	j	5b2 <main-0x11fffa4e>
 5b4:	0301                	addi	t1,t1,0
 5b6:	2d08                	fld	fa0,24(a0)
 5b8:	049f 03b8 03c6      	.insn	6, 0x03c603b8049f
 5be:	3002                	fld	ft0,32(sp)
 5c0:	049f 0488 04be      	.insn	6, 0x04be0488049f
 5c6:	3002                	fld	ft0,32(sp)
 5c8:	049f 04ec 058e      	.insn	6, 0x058e04ec049f
 5ce:	3002                	fld	ft0,32(sp)
 5d0:	009f 1412 6614      	.insn	6, 0x66141412009f
 5d6:	7166                	ld	sp,120(sp)
 5d8:	8d76                	mv	s10,t4
 5da:	9e01                	subw	a2,a2,s0
 5dc:	aa01                	j	6ec <main-0x11fff914>
 5de:	0401                	addi	s0,s0,0
 5e0:	01b4                	addi	a3,sp,200
 5e2:	01c0                	addi	s0,sp,196
 5e4:	3002                	fld	ft0,32(sp)
 5e6:	049f 01c0 038a      	.insn	6, 0x038a01c0049f
 5ec:	5801                	li	a6,-32
 5ee:	8a04                	.insn	2, 0x8a04
 5f0:	0303b003          	ld	zero,48(t2)
 5f4:	0182                	c.slli64	gp
 5f6:	049f 03c6 0488      	.insn	6, 0x048803c6049f
 5fc:	5801                	li	a6,-32
 5fe:	be04                	fsd	fs1,56(a2)
 600:	ec04                	sd	s1,24(s0)
 602:	0104                	addi	s1,sp,128
 604:	0058                	addi	a4,sp,4
 606:	211f 7c77 837c      	.insn	6, 0x837c7c77211f
 60c:	8301                	c.srli64	a4
 60e:	8701                	c.srai64	a4
 610:	9e01                	subw	a2,a2,s0
 612:	a801                	j	622 <main-0x11fff9de>
 614:	a801                	j	624 <main-0x11fff9dc>
 616:	aa01                	j	726 <main-0x11fff8da>
 618:	0401                	addi	s0,s0,0
 61a:	01e0                	addi	s0,sp,204
 61c:	01e4                	addi	s1,sp,204
 61e:	5801                	li	a6,-32
 620:	ca04                	sw	s1,16(a2)
 622:	0103dc03          	lhu	s8,16(t2)
 626:	0458                	addi	a4,sp,516
 628:	03dc                	addi	a5,sp,452
 62a:	03ec                	addi	a1,sp,460
 62c:	6d01                	.insn	2, 0x6d01
 62e:	ec04                	sd	s1,24(s0)
 630:	0303f603          	.insn	4, 0x0303f603
 634:	0282                	c.slli64	t0
 636:	049f 04be 04dd      	.insn	6, 0x04dd04be049f
 63c:	6d01                	.insn	2, 0x6d01
 63e:	dd04                	sw	s1,56(a0)
 640:	ec04                	sd	s1,24(s0)
 642:	0304                	addi	s1,sp,384
 644:	d891                	beqz	s1,558 <main-0x11fffaa8>
 646:	007e                	c.slli	zero,0x1f
 648:	2721                	addiw	a4,a4,8
 64a:	77762c27          	fsw	fs7,1912(a2)
 64e:	877d                	srai	a4,a4,0x1f
 650:	8701                	c.srai64	a4
 652:	8d01                	sub	a0,a0,s0
 654:	9e01                	subw	a2,a2,s0
 656:	aa01                	j	766 <main-0x11fff89a>
 658:	0401                	addi	s0,s0,0
 65a:	01e4                	addi	s1,sp,204
 65c:	0280                	addi	s0,sp,320
 65e:	3002                	fld	ft0,32(sp)
 660:	049f 0280 0292      	.insn	6, 0x02920280049f
 666:	6101                	addi	sp,sp,0
 668:	c604                	sw	s1,8(a2)
 66a:	0203ca03          	lbu	s4,32(t2)
 66e:	9f30                	.insn	2, 0x9f30
 670:	dc04                	sw	s1,56(s0)
 672:	0203f603          	.insn	4, 0x0203f603
 676:	9f30                	.insn	2, 0x9f30
 678:	f604                	sd	s1,40(a2)
 67a:	02048803          	lb	a6,32(s1)
 67e:	9f31                	addw	a4,a4,a2
 680:	be04                	fsd	fs1,56(a2)
 682:	ec04                	sd	s1,24(s0)
 684:	0204                	addi	s1,sp,256
 686:	9f30                	.insn	2, 0x9f30
 688:	2700                	fld	fs0,8(a4)
 68a:	2c2c                	fld	fa1,88(s0)
 68c:	372d                	addiw	a4,a4,-21
 68e:	4545                	li	a0,17
 690:	5948                	lw	a0,52(a0)
 692:	6464                	ld	s1,200(s0)
 694:	0465                	addi	s0,s0,25
 696:	0280                	addi	s0,sp,320
 698:	0292                	slli	t0,t0,0x4
 69a:	3002                	fld	ft0,32(sp)
 69c:	049f 0292 0294      	.insn	6, 0x02940292049f
 6a2:	5d01                	li	s10,-32
 6a4:	a204                	fsd	fs1,0(a2)
 6a6:	cd02                	sw	zero,152(sp)
 6a8:	0102                	c.slli64	sp
 6aa:	045d                	addi	s0,s0,23
 6ac:	02cd                	addi	t0,t0,19 # 174013 <main-0x11e8bfed>
 6ae:	02ce                	slli	t0,t0,0x13
 6b0:	7ee09103          	lh	sp,2030(ra)
 6b4:	e204                	sd	s1,0(a2)
 6b6:	f802                	sd	zero,48(sp)
 6b8:	0802                	c.slli64	a6
 6ba:	e091                	bnez	s1,6be <main-0x11fff942>
 6bc:	947e                	add	s0,s0,t6
 6be:	2304                	fld	fs1,0(a4)
 6c0:	9f01                	subw	a4,a4,s0
 6c2:	f804                	sd	s1,48(s0)
 6c4:	8202                	jr	tp
 6c6:	005d0103          	lb	sp,5(s10)
 6ca:	2d2c                	fld	fa1,88(a0)
 6cc:	5739                	li	a4,-18
 6ce:	9204                	.insn	2, 0x9204
 6d0:	9402                	jalr	s0
 6d2:	0302                	c.slli64	t1
 6d4:	3008                	fld	fa0,32(s0)
 6d6:	049f 02a6 02e2      	.insn	6, 0x02e202a6049f
 6dc:	9f300803          	lb	a6,-1549(zero) # fffffffffffff9f3 <__sheap+0xffffffffedffc9f3>
 6e0:	2c00                	fld	fs0,24(s0)
 6e2:	3e2d                	addiw	t3,t3,-21 # ffffffffffff4feb <__sheap+0xffffffffedff1feb>
 6e4:	0445                	addi	s0,s0,17
 6e6:	0292                	slli	t0,t0,0x4
 6e8:	0294                	addi	a3,sp,320
 6ea:	0309                	addi	t1,t1,2
 6ec:	2108                	fld	fa0,0(a0)
 6ee:	1200                	addi	s0,sp,288
 6f0:	0000                	unimp
 6f2:	0000                	unimp
 6f4:	a604                	fsd	fs1,8(a2)
 6f6:	cd02                	sw	zero,152(sp)
 6f8:	0902                	c.slli64	s2
 6fa:	00210803          	lb	a6,2(sp)
 6fe:	0012                	c.slli	zero,0x4
 700:	0000                	unimp
 702:	0000                	unimp
 704:	6a66                	ld	s4,88(sp)
 706:	6c6a                	ld	s8,152(sp)
 708:	018d018b          	.insn	4, 0x018d018b
 70c:	8a04                	.insn	2, 0x8a04
 70e:	01039403          	lh	s0,16(t2)
 712:	0458                	addi	a4,sp,516
 714:	0394                	addi	a3,sp,448
 716:	039c                	addi	a5,sp,448
 718:	9f017803          	.insn	4, 0x9f017803
 71c:	8604                	.insn	2, 0x8604
 71e:	8804                	.insn	2, 0x8804
 720:	0104                	addi	s1,sp,128
 722:	0058                	addi	a4,sp,4
 724:	0199018f          	.insn	4, 0x0199018f
 728:	01aa                	slli	gp,gp,0xa
 72a:	0400                	addi	s0,sp,512
 72c:	0488                	addi	a0,sp,576
 72e:	04ae                	slli	s1,s1,0xb
 730:	9f300803          	lb	a6,-1549(zero) # fffffffffffff9f3 <__sheap+0xffffffffedffc9f3>
 734:	ec04                	sd	s1,24(s0)
 736:	8e04                	.insn	2, 0x8e04
 738:	0305                	addi	t1,t1,1
 73a:	3008                	fld	fa0,32(s0)
 73c:	009f 01ae 01b2      	.insn	6, 0x01b201ae009f
 742:	01b2                	slli	gp,gp,0xc
 744:	01b5                	addi	gp,gp,13
 746:	ec04                	sd	s1,24(s0)
 748:	f604                	sd	s1,40(a2)
 74a:	0104                	addi	s1,sp,128
 74c:	045f 04f6 0585      	.insn	6, 0x058504f6045f
 752:	0309                	addi	t1,t1,2
 754:	2108                	fld	fa0,0(a0)
 756:	1200                	addi	s0,sp,288
 758:	0000                	unimp
 75a:	0000                	unimp
 75c:	7f00                	ld	s0,56(a4)
 75e:	019e0187          	.insn	4, 0x019e0187
 762:	01aa                	slli	gp,gp,0xa
 764:	dc04                	sw	s1,56(s0)
 766:	0303f603          	.insn	4, 0x0303f603
 76a:	2d08                	fld	fa0,24(a0)
 76c:	049f 04be 04ec      	.insn	6, 0x04ec04be049f
 772:	9f2d0803          	lb	a6,-1550(s10)
 776:	0000                	unimp
 778:	0808                	addi	a0,sp,16
 77a:	1a1a1313          	.insn	4, 0x1a1a1313
 77e:	1c1c                	addi	a5,sp,560
 780:	0400                	addi	s0,sp,512
 782:	2200                	fld	fs0,0(a2)
 784:	5a01                	li	s4,-32
 786:	2204                	fld	fs1,0(a2)
 788:	043c                	addi	a5,sp,520
 78a:	9f5a01a3          	sb	s5,-1565(s4)
 78e:	3c04                	fld	fs1,56(s0)
 790:	014a                	slli	sp,sp,0x12
 792:	045a                	slli	s0,s0,0x16
 794:	574a                	lw	a4,176(sp)
 796:	5e01                	li	t3,-32
 798:	5704                	lw	s1,40(a4)
 79a:	0182                	c.slli64	gp
 79c:	a304                	fsd	fs1,0(a4)
 79e:	5a01                	li	s4,-32
 7a0:	009f 100e 2804      	.insn	6, 0x2804100e009f
 7a6:	0d30                	addi	a2,sp,664
 7a8:	00210803          	lb	a6,2(sp)
 7ac:	0012                	c.slli	zero,0x4
 7ae:	0000                	unimp
 7b0:	0600                	addi	s0,sp,768
 7b2:	009f0123          	sb	s1,2(t5)
 7b6:	0070                	addi	a2,sp,12
 7b8:	0000                	unimp
 7ba:	0005                	c.nop	1
 7bc:	0008                	.insn	2, 0x0008
 7be:	0000                	unimp
 7c0:	0000                	unimp
 7c2:	0500                	addi	s0,sp,640
 7c4:	1905                	addi	s2,s2,-31
 7c6:	0019                	c.nop	6
 7c8:	0004                	.insn	2, 0x0004
 7ca:	045a010f          	.insn	4, 0x045a010f
 7ce:	5801240f          	.insn	4, 0x5801240f
 7d2:	2404                	fld	fs1,8(s0)
 7d4:	0428                	addi	a0,sp,520
 7d6:	9f5a01a3          	sb	s5,-1565(s4)
 7da:	0600                	addi	s0,sp,768
 7dc:	0d0d                	addi	s10,s10,3
 7de:	0400                	addi	s0,sp,512
 7e0:	1612                	slli	a2,a2,0x24
 7e2:	5a01                	li	s4,-32
 7e4:	1604                	addi	s1,sp,800
 7e6:	0128                	addi	a0,sp,136
 7e8:	1707005b          	.insn	4, 0x1707005b
 7ec:	1204                	addi	s1,sp,288
 7ee:	0120                	addi	s0,sp,136
 7f0:	0058                	addi	a4,sp,4
 7f2:	170d0d07          	.insn	4, 0x170d0d07
 7f6:	1204                	addi	s1,sp,288
 7f8:	0116                	slli	sp,sp,0x5
 7fa:	045a                	slli	s0,s0,0x16
 7fc:	2016                	fld	ft0,320(sp)
 7fe:	5b01                	li	s6,-32
 800:	0900                	addi	s0,sp,144
 802:	20120417          	auipc	s0,0x20120
 806:	3202                	fld	ft4,32(sp)
 808:	009f 1709 1204      	.insn	6, 0x12041709009f
 80e:	0120                	addi	s0,sp,136
 810:	0058                	addi	a4,sp,4
 812:	0d09                	addi	s10,s10,2
 814:	170d                	addi	a4,a4,-29
 816:	1204                	addi	s1,sp,288
 818:	0116                	slli	sp,sp,0x5
 81a:	045a                	slli	s0,s0,0x16
 81c:	2016                	fld	ft0,320(sp)
 81e:	5b01                	li	s6,-32
 820:	0900                	addi	s0,sp,144
 822:	20120417          	auipc	s0,0x20120
 826:	3002                	fld	ft0,32(sp)
 828:	009f 0017 0000      	.insn	6, 0x0017009f
 82e:	0005                	c.nop	1
 830:	0008                	.insn	2, 0x0008
 832:	0000                	unimp
 834:	0000                	unimp
 836:	0700                	addi	s0,sp,896
 838:	00040007          	.insn	4, 0x00040007
 83c:	0112                	slli	sp,sp,0x4
 83e:	045a                	slli	s0,s0,0x16
 840:	4012                	.insn	2, 0x4012
 842:	5801                	li	a6,-32
 844:	4e00                	lw	s0,24(a2)
 846:	0000                	unimp
 848:	0500                	addi	s0,sp,640
 84a:	0800                	addi	s0,sp,16
 84c:	0000                	unimp
 84e:	0000                	unimp
 850:	0800                	addi	s0,sp,16
 852:	0416                	slli	s0,s0,0x5
 854:	4032                	.insn	2, 0x4032
 856:	3102                	fld	ft2,32(sp)
 858:	009f 1608 3204      	.insn	6, 0x32041608009f
 85e:	0240                	addi	s0,sp,260
 860:	9f30                	.insn	2, 0x9f30
 862:	0400                	addi	s0,sp,512
 864:	26160413          	addi	s0,a2,609
 868:	3802                	fld	fa6,32(sp)
 86a:	009f 1304 1604      	.insn	6, 0x16041304009f
 870:	0226                	slli	tp,tp,0x9
 872:	9f30                	.insn	2, 0x9f30
 874:	0400                	addi	s0,sp,512
 876:	10000413          	li	s0,256
 87a:	3102                	fld	ft2,32(sp)
 87c:	009f 1304 0004      	.insn	6, 0x00041304009f
 882:	0210                	addi	a2,sp,256
 884:	9f30                	.insn	2, 0x9f30
 886:	1300                	addi	s0,sp,416
 888:	0400                	addi	s0,sp,512
 88a:	1610                	addi	a2,sp,800
 88c:	5a01                	li	s4,-32
 88e:	1600                	addi	s0,sp,800
 890:	0400                	addi	s0,sp,512
 892:	1610                	addi	a2,sp,800
 894:	5a01                	li	s4,-32
 896:	5600                	lw	s0,40(a2)
 898:	05000003          	lb	zero,80(zero) # 50 <main-0x11ffffb0>
 89c:	0800                	addi	s0,sp,16
 89e:	0000                	unimp
 8a0:	0000                	unimp
 8a2:	0000                	unimp
 8a4:	0a0a                	slli	s4,s4,0x2
 8a6:	100e                	c.slli	zero,0x23
 8a8:	1311                	addi	t1,t1,-28
 8aa:	1414                	addi	a3,sp,544
 8ac:	0600                	addi	s0,sp,768
 8ae:	0786                	slli	a5,a5,0x1
 8b0:	1200                	addi	s0,sp,288
 8b2:	0000                	unimp
 8b4:	0000                	unimp
 8b6:	0004                	.insn	2, 0x0004
 8b8:	0116                	slli	sp,sp,0x5
 8ba:	045a                	slli	s0,s0,0x16
 8bc:	1e16                	slli	t3,t3,0x25
 8be:	5a01                	li	s4,-32
 8c0:	2204                	fld	fs1,0(a2)
 8c2:	0128                	addi	a0,sp,136
 8c4:	045a                	slli	s0,s0,0x16
 8c6:	322c                	fld	fa1,96(a2)
 8c8:	5a01                	li	s4,-32
 8ca:	3204                	fld	fs1,32(a2)
 8cc:	0434                	addi	a3,sp,520
 8ce:	9f5a01a3          	sb	s5,-1565(s4)
 8d2:	0000                	unimp
 8d4:	0404                	addi	s1,sp,512
 8d6:	0b0b0807          	.insn	4, 0x0b0b0807
 8da:	100e                	c.slli	zero,0x23
 8dc:	06001313          	.insn	4, 0x06001313
 8e0:	0786                	slli	a5,a5,0x1
 8e2:	1200                	addi	s0,sp,288
 8e4:	0000                	unimp
 8e6:	0000                	unimp
 8e8:	0004                	.insn	2, 0x0004
 8ea:	0108                	addi	a0,sp,128
 8ec:	1008045b          	.insn	4, 0x1008045b
 8f0:	9f017b03          	.insn	4, 0x9f017b03
 8f4:	1004                	addi	s1,sp,32
 8f6:	0116                	slli	sp,sp,0x5
 8f8:	1e16045b          	.insn	4, 0x1e16045b
 8fc:	9f017b03          	.insn	4, 0x9f017b03
 900:	2204                	fld	fs1,0(a2)
 902:	032c                	addi	a1,sp,392
 904:	049f017b          	.insn	4, 0x049f017b
 908:	342c                	fld	fa1,104(s0)
 90a:	5b01                	li	s6,-32
 90c:	0000                	unimp
 90e:	0c0c                	addi	a1,sp,528
 910:	06001513          	.insn	4, 0x06001513
 914:	0754                	addi	a3,sp,900
 916:	1200                	addi	s0,sp,288
 918:	0000                	unimp
 91a:	0000                	unimp
 91c:	0004                	.insn	2, 0x0004
 91e:	0116                	slli	sp,sp,0x5
 920:	2616045b          	.insn	4, 0x2616045b
 924:	5b01                	li	s6,-32
 926:	2804                	fld	fs1,16(s0)
 928:	0132                	slli	sp,sp,0xc
 92a:	0503005b          	.insn	4, 0x0503005b
 92e:	1105                	addi	sp,sp,-31
 930:	1311                	addi	t1,t1,-28
 932:	54060013          	addi	zero,a2,1344
 936:	00120007          	.insn	4, 0x00120007
 93a:	0000                	unimp
 93c:	0400                	addi	s0,sp,512
 93e:	0800                	addi	s0,sp,16
 940:	5a01                	li	s4,-32
 942:	0804                	addi	s1,sp,16
 944:	0120                	addi	s0,sp,136
 946:	045f 2620 5a01      	.insn	6, 0x5a012620045f
 94c:	2604                	fld	fs1,8(a2)
 94e:	0132                	slli	sp,sp,0xc
 950:	005f 1000 0010      	.insn	6, 0x00101000005f
 956:	2206                	fld	ft4,64(sp)
 958:	00120007          	.insn	4, 0x00120007
 95c:	0000                	unimp
 95e:	0400                	addi	s0,sp,512
 960:	2600                	fld	fs0,8(a2)
 962:	5c01                	li	s8,-32
 964:	2604                	fld	fs1,8(a2)
 966:	0432                	slli	s0,s0,0xc
 968:	9f5c01a3          	sb	s5,-1565(s8)
 96c:	0200                	addi	s0,sp,256
 96e:	0800                	addi	s0,sp,16
 970:	0722                	slli	a4,a4,0x8
 972:	1200                	addi	s0,sp,288
 974:	0000                	unimp
 976:	0000                	unimp
 978:	0132                	slli	sp,sp,0xc
 97a:	005a                	c.slli	zero,0x16
 97c:	0704                	addi	s1,sp,896
 97e:	0f0b0a07          	.insn	4, 0x0f0b0a07
 982:	1310                	addi	a2,sp,416
 984:	15141413          	.insn	4, 0x15141413
 988:	2206                	fld	ft4,64(sp)
 98a:	00120007          	.insn	4, 0x00120007
 98e:	0000                	unimp
 990:	0400                	addi	s0,sp,512
 992:	0600                	addi	s0,sp,768
 994:	3002                	fld	ft0,32(sp)
 996:	049f 1006 5f01      	.insn	6, 0x5f011006049f
 99c:	1004                	addi	s1,sp,32
 99e:	0122                	slli	sp,sp,0x8
 9a0:	045f 2a26 7f06      	.insn	6, 0x7f062a26045f
 9a6:	7a00                	ld	s0,48(a2)
 9a8:	1c00                	addi	s0,sp,560
 9aa:	049f 2c2a 7f08      	.insn	6, 0x7f082c2a049f
 9b0:	7a00                	ld	s0,48(a2)
 9b2:	1c00                	addi	s0,sp,560
 9b4:	049f0123          	sb	s1,66(t5)
 9b8:	302c                	fld	fa1,96(s0)
 9ba:	7f06                	ld	t5,96(sp)
 9bc:	7a00                	ld	s0,48(a2)
 9be:	1c00                	addi	s0,sp,560
 9c0:	009f 0700 0007      	.insn	6, 0x00070700009f
 9c6:	1006                	c.slli	zero,0x21
 9c8:	00120007          	.insn	4, 0x00120007
 9cc:	0000                	unimp
 9ce:	0400                	addi	s0,sp,512
 9d0:	0800                	addi	s0,sp,16
 9d2:	5b01                	li	s6,-32
 9d4:	0804                	addi	s1,sp,16
 9d6:	0112                	slli	sp,sp,0x4
 9d8:	0402005b          	.insn	4, 0x0402005b
 9dc:	0004                	.insn	2, 0x0004
 9de:	1006                	c.slli	zero,0x21
 9e0:	00120007          	.insn	4, 0x00120007
 9e4:	0000                	unimp
 9e6:	0400                	addi	s0,sp,512
 9e8:	0200                	addi	s0,sp,256
 9ea:	5a01                	li	s4,-32
 9ec:	0204                	addi	s1,sp,256
 9ee:	0112                	slli	sp,sp,0x4
 9f0:	005f 0a00 0b0a      	.insn	6, 0x0b0a0a00005f
 9f6:	000c0c0b          	.insn	4, 0x000c0c0b
 9fa:	f606                	sd	ra,296(sp)
 9fc:	0006                	c.slli	zero,0x1
 9fe:	0012                	c.slli	zero,0x4
 a00:	0000                	unimp
 a02:	0400                	addi	s0,sp,512
 a04:	1400                	addi	s0,sp,544
 a06:	5a01                	li	s4,-32
 a08:	1404                	addi	s1,sp,544
 a0a:	0416                	slli	s0,s0,0x5
 a0c:	9f5a01a3          	sb	s5,-1565(s4)
 a10:	1604                	addi	s1,sp,800
 a12:	0118                	addi	a4,sp,128
 a14:	045a                	slli	s0,s0,0x16
 a16:	1a18                	addi	a4,sp,304
 a18:	a304                	fsd	fs1,0(a4)
 a1a:	5a01                	li	s4,-32
 a1c:	009f 0503 0b05      	.insn	6, 0x0b050503009f
 a22:	000c0c0b          	.insn	4, 0x000c0c0b
 a26:	f606                	sd	ra,296(sp)
 a28:	0006                	c.slli	zero,0x1
 a2a:	0012                	c.slli	zero,0x4
 a2c:	0000                	unimp
 a2e:	0400                	addi	s0,sp,512
 a30:	0800                	addi	s0,sp,16
 a32:	5a01                	li	s4,-32
 a34:	0804                	addi	s1,sp,16
 a36:	0116                	slli	sp,sp,0x5
 a38:	045f 1816 5a01      	.insn	6, 0x5a011816045f
 a3e:	1804                	addi	s1,sp,48
 a40:	041a                	slli	s0,s0,0x6
 a42:	9f5a01a3          	sb	s5,-1565(s4)
 a46:	0000                	unimp
 a48:	06000707          	.insn	4, 0x06000707
 a4c:	06d2                	slli	a3,a3,0x14
 a4e:	1200                	addi	s0,sp,288
 a50:	0000                	unimp
 a52:	0000                	unimp
 a54:	0004                	.insn	2, 0x0004
 a56:	0106                	slli	sp,sp,0x1
 a58:	045a                	slli	s0,s0,0x16
 a5a:	2406                	fld	fs0,64(sp)
 a5c:	a304                	fsd	fs1,0(a4)
 a5e:	5a01                	li	s4,-32
 a60:	009f 0700 0007      	.insn	6, 0x00070700009f
 a66:	d206                	sw	ra,36(sp)
 a68:	0006                	c.slli	zero,0x1
 a6a:	0012                	c.slli	zero,0x4
 a6c:	0000                	unimp
 a6e:	0400                	addi	s0,sp,512
 a70:	0600                	addi	s0,sp,768
 a72:	5b01                	li	s6,-32
 a74:	0604                	addi	s1,sp,768
 a76:	0424                	addi	s1,sp,520
 a78:	9f5b01a3          	sb	s5,-1565(s6)
 a7c:	0000                	unimp
 a7e:	0606                	slli	a2,a2,0x1
 a80:	0600                	addi	s0,sp,768
 a82:	06d2                	slli	a3,a3,0x14
 a84:	1200                	addi	s0,sp,288
 a86:	0000                	unimp
 a88:	0000                	unimp
 a8a:	0004                	.insn	2, 0x0004
 a8c:	0104                	addi	s1,sp,128
 a8e:	045c                	addi	a5,sp,516
 a90:	2404                	fld	fs1,8(s0)
 a92:	a304                	fsd	fs1,0(a4)
 a94:	5c01                	li	s8,-32
 a96:	009f 0702 0007      	.insn	6, 0x00070702009f
 a9c:	d206                	sw	ra,36(sp)
 a9e:	0006                	c.slli	zero,0x1
 aa0:	0012                	c.slli	zero,0x4
 aa2:	0000                	unimp
 aa4:	0400                	addi	s0,sp,512
 aa6:	0600                	addi	s0,sp,768
 aa8:	5a01                	li	s4,-32
 aaa:	0604                	addi	s1,sp,768
 aac:	0424                	addi	s1,sp,520
 aae:	9f5a01a3          	sb	s5,-1565(s4)
 ab2:	0300                	addi	s0,sp,384
 ab4:	06000707          	.insn	4, 0x06000707
 ab8:	06d2                	slli	a3,a3,0x14
 aba:	1200                	addi	s0,sp,288
 abc:	0000                	unimp
 abe:	0000                	unimp
 ac0:	0004                	.insn	2, 0x0004
 ac2:	0106                	slli	sp,sp,0x1
 ac4:	2406045b          	.insn	4, 0x2406045b
 ac8:	a304                	fsd	fs1,0(a4)
 aca:	5b01                	li	s6,-32
 acc:	009f 0705 0a07      	.insn	6, 0x0a070705009f
 ad2:	0e0a                	slli	t3,t3,0x2
 ad4:	120e                	slli	tp,tp,0x23
 ad6:	d206                	sw	ra,36(sp)
 ad8:	0006                	c.slli	zero,0x1
 ada:	0012                	c.slli	zero,0x4
 adc:	0000                	unimp
 ade:	0400                	addi	s0,sp,512
 ae0:	0600                	addi	s0,sp,768
 ae2:	3002                	fld	ft0,32(sp)
 ae4:	049f 0a06 7a07      	.insn	6, 0x7a070a06049f
 aea:	a300                	fsd	fs0,0(a4)
 aec:	5a01                	li	s4,-32
 aee:	9f1c                	.insn	2, 0x9f1c
 af0:	0a04                	addi	s1,sp,272
 af2:	0914                	addi	a3,sp,144
 af4:	007a                	c.slli	zero,0x1e
 af6:	1c5a01a3          	sb	t0,451(s4)
 afa:	049f0123          	sb	s1,66(t5)
 afe:	1e14                	addi	a3,sp,816
 b00:	a3007a07          	.insn	4, 0xa3007a07
 b04:	5a01                	li	s4,-32
 b06:	9f1c                	.insn	2, 0x9f1c
 b08:	0000                	unimp
 b0a:	06000707          	.insn	4, 0x06000707
 b0e:	06ba                	slli	a3,a3,0xe
 b10:	1200                	addi	s0,sp,288
 b12:	0000                	unimp
 b14:	0000                	unimp
 b16:	0004                	.insn	2, 0x0004
 b18:	0106                	slli	sp,sp,0x1
 b1a:	1806045b          	.insn	4, 0x1806045b
 b1e:	a304                	fsd	fs1,0(a4)
 b20:	5b01                	li	s6,-32
 b22:	009f 0500 0605      	.insn	6, 0x06050500009f
 b28:	0e06                	slli	t3,t3,0x1
 b2a:	ba06                	fsd	ft1,304(sp)
 b2c:	0006                	c.slli	zero,0x1
 b2e:	0012                	c.slli	zero,0x4
 b30:	0000                	unimp
 b32:	0400                	addi	s0,sp,512
 b34:	0000                	unimp
 b36:	5c01                	li	s8,-32
 b38:	0004                	.insn	2, 0x0004
 b3a:	0304                	addi	s1,sp,384
 b3c:	7f7c                	ld	a5,248(a4)
 b3e:	049f 1604 a306      	.insn	6, 0xa3061604049f
 b44:	5c01                	li	s8,-32
 b46:	1c31                	addi	s8,s8,-20
 b48:	009f 0704 0a07      	.insn	6, 0x0a070704009f
 b4e:	0b0a                	slli	s6,s6,0x2
 b50:	ba060e0b          	.insn	4, 0xba060e0b
 b54:	0006                	c.slli	zero,0x1
 b56:	0012                	c.slli	zero,0x4
 b58:	0000                	unimp
 b5a:	0400                	addi	s0,sp,512
 b5c:	0600                	addi	s0,sp,768
 b5e:	5a01                	li	s4,-32
 b60:	0604                	addi	s1,sp,768
 b62:	010c                	addi	a1,sp,128
 b64:	045f 0e0c 7f03      	.insn	6, 0x7f030e0c045f
 b6a:	0e049f7f 005f0116 	.insn	12, 0xba080004005f01160e049f7f
 b72:	ba080004 
 b76:	0006                	c.slli	zero,0x1
 b78:	0012                	c.slli	zero,0x4
 b7a:	0000                	unimp
 b7c:	1800                	addi	s0,sp,48
 b7e:	5b01                	li	s6,-32
 b80:	0000                	unimp
 b82:	0404                	addi	s1,sp,512
 b84:	0505                	addi	a0,a0,1
 b86:	0606                	slli	a2,a2,0x1
 b88:	0808                	addi	a0,sp,16
 b8a:	0a0a                	slli	s4,s4,0x2
 b8c:	06a8060b          	.insn	4, 0x06a8060b
 b90:	1200                	addi	s0,sp,288
 b92:	0000                	unimp
 b94:	0000                	unimp
 b96:	0004                	.insn	2, 0x0004
 b98:	0100                	addi	s0,sp,128
 b9a:	045c                	addi	a5,sp,516
 b9c:	0400                	addi	s0,sp,512
 b9e:	9f7f7c03          	.insn	4, 0x9f7f7c03
 ba2:	0404                	addi	s1,sp,512
 ba4:	0606                	slli	a2,a2,0x1
 ba6:	315c01a3          	sb	s5,771(s8)
 baa:	9f1c                	.insn	2, 0x9f1c
 bac:	0604                	addi	s1,sp,768
 bae:	0b08                	addi	a0,sp,400
 bb0:	007f a320 5c01 7a22 	.insn	10, 0x22007a225c01a320007f
 bb8:	2200 
 bba:	049f 0c08 7a0a      	.insn	6, 0x7a0a0c08049f
 bc0:	7f00                	ld	s0,56(a4)
 bc2:	1c00                	addi	s0,sp,560
 bc4:	225c01a3          	sb	t0,547(s8)
 bc8:	049f 100c 7f0b      	.insn	6, 0x7f0b100c049f
 bce:	2000                	fld	fs0,0(s0)
 bd0:	225c01a3          	sb	t0,547(s8)
 bd4:	007a                	c.slli	zero,0x1e
 bd6:	9f22                	add	t5,t5,s0
 bd8:	0300                	addi	s0,sp,384
 bda:	0606                	slli	a2,a2,0x1
 bdc:	06a8060b          	.insn	4, 0x06a8060b
 be0:	1200                	addi	s0,sp,288
 be2:	0000                	unimp
 be4:	0000                	unimp
 be6:	0004                	.insn	2, 0x0004
 be8:	0106                	slli	sp,sp,0x1
 bea:	045a                	slli	s0,s0,0x16
 bec:	1006                	c.slli	zero,0x21
 bee:	5f01                	li	t5,-32
	...

Disassembly of section .debug_aranges:

0000000000000000 <.debug_aranges>:
   0:	002c                	addi	a1,sp,8
   2:	0000                	unimp
   4:	0002                	c.slli64	zero
   6:	0000                	unimp
   8:	0000                	unimp
   a:	0008                	.insn	2, 0x0008
   c:	0000                	unimp
   e:	0000                	unimp
  10:	0000                	unimp
  12:	1200                	addi	s0,sp,288
  14:	0000                	unimp
  16:	0000                	unimp
  18:	0040                	addi	s0,sp,4
	...
  2e:	0000                	unimp
  30:	002c                	addi	a1,sp,8
  32:	0000                	unimp
  34:	0002                	c.slli64	zero
  36:	00000173          	.insn	4, 0x0173
  3a:	0008                	.insn	2, 0x0008
  3c:	0000                	unimp
  3e:	0000                	unimp
  40:	0040                	addi	s0,sp,4
  42:	1200                	addi	s0,sp,288
  44:	0000                	unimp
  46:	0000                	unimp
  48:	057a                	slli	a0,a0,0x1e
	...
  5e:	0000                	unimp
  60:	002c                	addi	a1,sp,8
  62:	0000                	unimp
  64:	0002                	c.slli64	zero
  66:	0ab4                	addi	a3,sp,344
  68:	0000                	unimp
  6a:	0008                	.insn	2, 0x0008
  6c:	0000                	unimp
  6e:	0000                	unimp
  70:	05ba                	slli	a1,a1,0xe
  72:	1200                	addi	s0,sp,288
  74:	0000                	unimp
  76:	0000                	unimp
  78:	0028                	addi	a0,sp,8
	...
  8e:	0000                	unimp
  90:	002c                	addi	a1,sp,8
  92:	0000                	unimp
  94:	0002                	c.slli64	zero
  96:	0d5e                	slli	s10,s10,0x17
  98:	0000                	unimp
  9a:	0008                	.insn	2, 0x0008
  9c:	0000                	unimp
  9e:	0000                	unimp
  a0:	05e2                	slli	a1,a1,0x18
  a2:	1200                	addi	s0,sp,288
  a4:	0000                	unimp
  a6:	0000                	unimp
  a8:	004c                	addi	a1,sp,4
	...
  be:	0000                	unimp
  c0:	002c                	addi	a1,sp,8
  c2:	0000                	unimp
  c4:	0002                	c.slli64	zero
  c6:	0f00                	addi	s0,sp,912
  c8:	0000                	unimp
  ca:	0008                	.insn	2, 0x0008
  cc:	0000                	unimp
  ce:	0000                	unimp
  d0:	062e                	slli	a2,a2,0xb
  d2:	1200                	addi	s0,sp,288
  d4:	0000                	unimp
  d6:	0000                	unimp
  d8:	004a                	c.slli	zero,0x12
	...
  ee:	0000                	unimp
  f0:	002c                	addi	a1,sp,8
  f2:	0000                	unimp
  f4:	0002                	c.slli64	zero
  f6:	13b2                	slli	t2,t2,0x2c
  f8:	0000                	unimp
  fa:	0008                	.insn	2, 0x0008
  fc:	0000                	unimp
  fe:	0000                	unimp
 100:	0678                	addi	a4,sp,780
 102:	1200                	addi	s0,sp,288
 104:	0000                	unimp
 106:	0000                	unimp
 108:	0018                	.insn	2, 0x0018
	...
 11e:	0000                	unimp
 120:	002c                	addi	a1,sp,8
 122:	0000                	unimp
 124:	0002                	c.slli64	zero
 126:	000014b7          	lui	s1,0x1
 12a:	0008                	.insn	2, 0x0008
 12c:	0000                	unimp
 12e:	0000                	unimp
 130:	0690                	addi	a2,sp,832
 132:	1200                	addi	s0,sp,288
 134:	0000                	unimp
 136:	0000                	unimp
 138:	0018                	.insn	2, 0x0018
	...
 14e:	0000                	unimp
 150:	002c                	addi	a1,sp,8
 152:	0000                	unimp
 154:	0002                	c.slli64	zero
 156:	14df 0000 0008      	.insn	6, 0x0008000014df
 15c:	0000                	unimp
 15e:	0000                	unimp
 160:	06a8                	addi	a0,sp,840
 162:	1200                	addi	s0,sp,288
 164:	0000                	unimp
 166:	0000                	unimp
 168:	0112                	slli	sp,sp,0x4
	...

Disassembly of section .debug_rnglists:

0000000000000000 <.debug_rnglists>:
   0:	00000013          	nop
   4:	0005                	c.nop	1
   6:	0008                	.insn	2, 0x0008
   8:	0000                	unimp
   a:	0000                	unimp
   c:	00000007          	.insn	4, 0x0007
  10:	0012                	c.slli	zero,0x4
  12:	0000                	unimp
  14:	4000                	lw	s0,0(s0)
  16:	3b00                	fld	fs0,48(a4)
  18:	0001                	nop
  1a:	0500                	addi	s0,sp,640
  1c:	0800                	addi	s0,sp,16
  1e:	0000                	unimp
  20:	0000                	unimp
  22:	0400                	addi	s0,sp,512
  24:	2828                	fld	fa0,80(s0)
  26:	3004                	fld	fs1,32(s0)
  28:	0436                	slli	s0,s0,0xd
  2a:	8062                	c.mv	zero,s8
  2c:	0001                	nop
  2e:	3c04                	fld	fs1,56(s0)
  30:	0448                	addi	a0,sp,516
  32:	6248                	ld	a0,128(a2)
  34:	0400                	addi	s0,sp,512
  36:	01ec                	addi	a1,sp,204
  38:	01f6                	slli	gp,gp,0x1d
  3a:	8804                	.insn	2, 0x8804
  3c:	ae04                	fsd	fs1,24(a2)
  3e:	0404                	addi	s1,sp,512
  40:	04b0                	addi	a2,sp,584
  42:	04b8                	addi	a4,sp,584
  44:	ec04                	sd	s1,24(s0)
  46:	8e04                	.insn	2, 0x8e04
  48:	0005                	c.nop	1
  4a:	8004                	.insn	2, 0x8004
  4c:	8a02                	jr	s4
  4e:	04840403          	lb	s0,72(s0) # 2012086a <__sheap+0xe11d86a>
  52:	0486                	slli	s1,s1,0x1
  54:	0400                	addi	s0,sp,512
  56:	0288                	addi	a0,sp,320
  58:	029a                	slli	t0,t0,0x6
  5a:	9c04                	.insn	2, 0x9c04
  5c:	a202                	fsd	ft0,256(sp)
  5e:	0402                	c.slli64	s0
  60:	02a6                	slli	t0,t0,0x9
  62:	02ce                	slli	t0,t0,0x13
  64:	ce04                	sw	s1,24(a2)
  66:	d202                	sw	zero,36(sp)
  68:	0402                	c.slli64	s0
  6a:	02d6                	slli	t0,t0,0x15
  6c:	02e2                	slli	t0,t0,0x18
  6e:	ea04                	sd	s1,16(a2)
  70:	ec02                	sd	zero,24(sp)
  72:	0402                	c.slli64	s0
  74:	02f0                	addi	a2,sp,332
  76:	02f6                	slli	t0,t0,0x1d
  78:	0400                	addi	s0,sp,512
  7a:	02a6                	slli	t0,t0,0x9
  7c:	02b2                	slli	t0,t0,0xc
  7e:	c204                	sw	s1,0(a2)
  80:	ce02                	sw	zero,28(sp)
  82:	0002                	c.slli64	zero
  84:	8a04                	.insn	2, 0x8a04
  86:	04039e03          	lh	t3,64(t2)
  8a:	0486                	slli	s1,s1,0x1
  8c:	0488                	addi	a0,sp,576
  8e:	0400                	addi	s0,sp,512
  90:	03ca                	slli	t2,t2,0x12
  92:	03d8                	addi	a4,sp,452
  94:	dc04                	sw	s1,56(s0)
  96:	0403f603          	.insn	4, 0x0403f603
  9a:	03f6                	slli	t2,t2,0x1d
  9c:	03f8                	addi	a4,sp,460
  9e:	be04                	fsd	fs1,56(a2)
  a0:	ec04                	sd	s1,24(s0)
  a2:	0004                	.insn	2, 0x0004
  a4:	be04                	fsd	fs1,56(a2)
  a6:	d004                	sw	s1,32(s0)
  a8:	0404                	addi	s1,sp,512
  aa:	04d0                	addi	a2,sp,580
  ac:	04ec                	addi	a1,sp,588
  ae:	0400                	addi	s0,sp,512
  b0:	058e                	slli	a1,a1,0x3
  b2:	058e                	slli	a1,a1,0x3
  b4:	9a04                	.insn	2, 0x9a04
  b6:	b205                	j	fffffffffffff9d6 <__sheap+0xffffffffedffc9d6>
  b8:	0405                	addi	s0,s0,1
  ba:	05bc                	addi	a5,sp,712
  bc:	0696                	slli	a3,a3,0x5
  be:	ac04                	fsd	fs1,24(s0)
  c0:	9006                	c.add	zero,ra
  c2:	0409                	addi	s0,s0,2
  c4:	09bc                	addi	a5,sp,216
  c6:	09d4                	addi	a3,sp,212
  c8:	e004                	sd	s1,0(s0)
  ca:	d209                	beqz	a2,ffffffffffffffcc <__sheap+0xffffffffedffcfcc>
  cc:	000a                	c.slli	zero,0x2
  ce:	c004                	sw	s1,0(s0)
  d0:	d406                	sw	ra,40(sp)
  d2:	0406                	slli	s0,s0,0x1
  d4:	06d6                	slli	a3,a3,0x15
  d6:	06dc                	addi	a5,sp,836
  d8:	0400                	addi	s0,sp,512
  da:	06dc                	addi	a5,sp,836
  dc:	078c                	addi	a1,sp,960
  de:	8e04                	.insn	2, 0x8e04
  e0:	04079007          	.insn	4, 0x04079007
  e4:	0ac6                	slli	s5,s5,0x11
  e6:	0ad2                	slli	s5,s5,0x14
  e8:	0400                	addi	s0,sp,512
  ea:	06e2                	slli	a3,a3,0x18
  ec:	0788                	addi	a0,sp,960
  ee:	c604                	sw	s1,8(a2)
  f0:	d20a                	sw	sp,36(sp)
  f2:	000a                	c.slli	zero,0x2
  f4:	9004                	.insn	2, 0x9004
  f6:	0407c007          	.insn	4, 0x0407c007
  fa:	07c2                	slli	a5,a5,0x10
  fc:	07c6                	slli	a5,a5,0x11
  fe:	0400                	addi	s0,sp,512
 100:	0790                	addi	a2,sp,960
 102:	0794                	addi	a3,sp,960
 104:	9804                	.insn	2, 0x9804
 106:	0007ac07          	flw	fs8,0(a5)
 10a:	c604                	sw	s1,8(a2)
 10c:	0407da07          	.insn	4, 0x0407da07
 110:	07dc                	addi	a5,sp,964
 112:	07e0                	addi	s0,sp,972
 114:	0400                	addi	s0,sp,512
 116:	089c                	addi	a5,sp,80
 118:	08b0                	addi	a2,sp,88
 11a:	b204                	fsd	fs1,32(a2)
 11c:	b608                	fsd	fa0,40(a2)
 11e:	0008                	.insn	2, 0x0008
 120:	b604                	fsd	fs1,40(a2)
 122:	c608                	sw	a0,8(a2)
 124:	0408                	addi	a0,sp,512
 126:	08c8                	addi	a0,sp,84
 128:	08ca                	slli	a7,a7,0x12
 12a:	0400                	addi	s0,sp,512
 12c:	08ca                	slli	a7,a7,0x12
 12e:	08de                	slli	a7,a7,0x17
 130:	e004                	sd	s1,0(s0)
 132:	e408                	sd	a0,8(s0)
 134:	0008                	.insn	2, 0x0008
 136:	e404                	sd	s1,8(s0)
 138:	8608                	.insn	2, 0x8608
 13a:	0409                	addi	s0,s0,2
 13c:	098a                	slli	s3,s3,0x2
 13e:	098e                	slli	s3,s3,0x3
 140:	a804                	fsd	fs1,16(s0)
 142:	c60a                	sw	sp,12(sp)
 144:	000a                	c.slli	zero,0x2
 146:	9604                	.insn	2, 0x9604
 148:	9e06                	add	t3,t3,ra
 14a:	0406                	slli	s0,s0,0x1
 14c:	0990                	addi	a2,sp,208
 14e:	09a6                	slli	s3,s3,0x9
 150:	ac04                	fsd	fs1,24(s0)
 152:	b409                	j	fffffffffffffb54 <__sheap+0xffffffffedffcb54>
 154:	0009                	c.nop	2
 156:	0014                	.insn	2, 0x0014
 158:	0000                	unimp
 15a:	0005                	c.nop	1
 15c:	0008                	.insn	2, 0x0008
 15e:	0000                	unimp
 160:	0000                	unimp
 162:	0006a807          	flw	fa6,0(a3)
 166:	0012                	c.slli	zero,0x4
 168:	0000                	unimp
 16a:	9200                	.insn	2, 0x9200
 16c:	0002                	c.slli64	zero

Disassembly of section .debug_line:

0000000000000000 <.debug_line>:
       0:	00a5                	addi	ra,ra,9
       2:	0000                	unimp
       4:	0005                	c.nop	1
       6:	0008                	.insn	2, 0x0008
       8:	0041                	c.nop	16
       a:	0000                	unimp
       c:	0101                	addi	sp,sp,0
       e:	f601                	bnez	a2,ffffffffffffff16 <__sheap+0xffffffffedffcf16>
      10:	0df2                	slli	s11,s11,0x1c
      12:	0100                	addi	s0,sp,128
      14:	0101                	addi	sp,sp,0
      16:	0001                	nop
      18:	0000                	unimp
      1a:	0001                	nop
      1c:	0100                	addi	s0,sp,128
      1e:	0101                	addi	sp,sp,0
      20:	031f 004d 0000      	.insn	6, 0x004d031f
      26:	007c                	addi	a5,sp,12
      28:	0000                	unimp
      2a:	0000                	unimp
      2c:	0000                	unimp
      2e:	0102                	c.slli64	sp
      30:	021f 050b 0046      	.insn	6, 0x0046050b021f
      36:	0000                	unimp
      38:	4600                	lw	s0,8(a2)
      3a:	0000                	unimp
      3c:	0000                	unimp
      3e:	00000033          	add	zero,zero,zero
      42:	2c01                	sext.w	s8,s8
      44:	0000                	unimp
      46:	0200                	addi	s0,sp,256
      48:	003d                	c.nop	15
      4a:	0000                	unimp
      4c:	0001                	nop
      4e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
      50:	0000                	unimp
      52:	1200                	addi	s0,sp,288
      54:	0000                	unimp
      56:	0000                	unimp
      58:	0520                	addi	s0,sp,648
      5a:	091e                	slli	s2,s2,0x7
      5c:	0000                	unimp
      5e:	0518                	addi	a4,sp,640
      60:	0905                	addi	s2,s2,1
      62:	0000                	unimp
      64:	1606                	slli	a2,a2,0x21
      66:	1e05                	addi	t3,t3,-31
      68:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
      6a:	1800                	addi	s0,sp,48
      6c:	0505                	addi	a0,a0,1
      6e:	0809                	addi	a6,a6,2
      70:	1600                	addi	s0,sp,800
      72:	1e05                	addi	t3,t3,-31
      74:	0c09                	addi	s8,s8,2
      76:	1800                	addi	s0,sp,48
      78:	0505                	addi	a0,a0,1
      7a:	0809                	addi	a6,a6,2
      7c:	0600                	addi	s0,sp,768
      7e:	0519                	addi	a0,a0,6
      80:	0905                	addi	s2,s2,1
      82:	0000                	unimp
      84:	0518                	addi	a4,sp,640
      86:	0909                	addi	s2,s2,2
      88:	0018                	.insn	2, 0x0018
      8a:	0200                	addi	s0,sp,256
      8c:	0204                	addi	s1,sp,256
      8e:	0518                	addi	a4,sp,640
      90:	0909                	addi	s2,s2,2
      92:	0008                	.insn	2, 0x0008
      94:	0200                	addi	s0,sp,256
      96:	0004                	.insn	2, 0x0004
      98:	0515                	addi	a0,a0,5
      9a:	0005                	c.nop	1
      9c:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
      9e:	0040                	addi	s0,sp,4
      a0:	1200                	addi	s0,sp,288
      a2:	0000                	unimp
      a4:	0000                	unimp
      a6:	0100                	addi	s0,sp,128
      a8:	2201                	sext.w	tp,tp
      aa:	000d                	c.nop	3
      ac:	0500                	addi	s0,sp,640
      ae:	0800                	addi	s0,sp,16
      b0:	4600                	lw	s0,8(a2)
      b2:	0000                	unimp
      b4:	0100                	addi	s0,sp,128
      b6:	0101                	addi	sp,sp,0
      b8:	f2f6                	sd	t4,352(sp)
      ba:	000d                	c.nop	3
      bc:	0101                	addi	sp,sp,0
      be:	0101                	addi	sp,sp,0
      c0:	0000                	unimp
      c2:	0100                	addi	s0,sp,128
      c4:	0000                	unimp
      c6:	0101                	addi	sp,sp,0
      c8:	1f01                	addi	t5,t5,-32
      ca:	00013c03          	ld	s8,0(sp)
      ce:	7c00                	ld	s0,56(s0)
      d0:	0000                	unimp
      d2:	b800                	fsd	fs0,48(s0)
      d4:	0000                	unimp
      d6:	0200                	addi	s0,sp,256
      d8:	1f01                	addi	t5,t5,-32
      da:	0b02                	c.slli64	s6
      dc:	a606                	fsd	ft1,264(sp)
      de:	0000                	unimp
      e0:	0000                	unimp
      e2:	00a6                	slli	ra,ra,0x9
      e4:	0000                	unimp
      e6:	af00                	fsd	fs0,24(a4)
      e8:	0000                	unimp
      ea:	0200                	addi	s0,sp,256
      ec:	00000033          	add	zero,zero,zero
      f0:	3d01                	addiw	s10,s10,-32
      f2:	0000                	unimp
      f4:	0100                	addi	s0,sp,128
      f6:	0134                	addi	a3,sp,136
      f8:	0000                	unimp
      fa:	0001                	nop
      fc:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
      fe:	0040                	addi	s0,sp,4
     100:	1200                	addi	s0,sp,288
     102:	0000                	unimp
     104:	0000                	unimp
     106:	052c                	addi	a1,sp,648
     108:	0901                	addi	s2,s2,0
     10a:	0000                	unimp
     10c:	0518                	addi	a4,sp,640
     10e:	0905                	addi	s2,s2,1
     110:	0000                	unimp
     112:	0106                	slli	sp,sp,0x1
     114:	1305                	addi	t1,t1,-31
     116:	0809                	addi	a6,a6,2
     118:	1600                	addi	s0,sp,800
     11a:	0105                	addi	sp,sp,1
     11c:	0409                	addi	s0,s0,2
     11e:	1800                	addi	s0,sp,48
     120:	0805                	addi	a6,a6,1
     122:	0409                	addi	s0,s0,2
     124:	1600                	addi	s0,sp,800
     126:	0105                	addi	sp,sp,1
     128:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     12a:	1800                	addi	s0,sp,48
     12c:	0805                	addi	a6,a6,1
     12e:	0409                	addi	s0,s0,2
     130:	1a00                	addi	s0,sp,304
     132:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     134:	0c09                	addi	s8,s8,2
     136:	0600                	addi	s0,sp,768
     138:	0501                	addi	a0,a0,0
     13a:	0905                	addi	s2,s2,1
     13c:	0000                	unimp
     13e:	0106                	slli	sp,sp,0x1
     140:	1605                	addi	a2,a2,-31
     142:	0609                	addi	a2,a2,2
     144:	0600                	addi	s0,sp,768
     146:	0518                	addi	a4,sp,640
     148:	0905                	addi	s2,s2,1
     14a:	0000                	unimp
     14c:	0518                	addi	a4,sp,640
     14e:	0909                	addi	s2,s2,2
     150:	0000                	unimp
     152:	05017003          	.insn	4, 0x05017003
     156:	0901                	addi	s2,s2,0
     158:	0000                	unimp
     15a:	0518                	addi	a4,sp,640
     15c:	0905                	addi	s2,s2,1
     15e:	0000                	unimp
     160:	0518                	addi	a4,sp,640
     162:	0905                	addi	s2,s2,1
     164:	0000                	unimp
     166:	2306                	fld	ft6,64(sp)
     168:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     16a:	0809                	addi	a6,a6,2
     16c:	0300                	addi	s0,sp,384
     16e:	0174                	addi	a3,sp,140
     170:	0805                	addi	a6,a6,1
     172:	0609                	addi	a2,a2,2
     174:	0100                	addi	s0,sp,128
     176:	0805                	addi	a6,a6,1
     178:	0009                	c.nop	2
     17a:	2800                	fld	fs0,16(s0)
     17c:	0105                	addi	sp,sp,1
     17e:	0609                	addi	a2,a2,2
     180:	0300                	addi	s0,sp,384
     182:	0170                	addi	a2,sp,140
     184:	1805                	addi	a6,a6,-31
     186:	0c09                	addi	s8,s8,2
     188:	0600                	addi	s0,sp,768
     18a:	0520                	addi	s0,sp,648
     18c:	0909                	addi	s2,s2,2
     18e:	0000                	unimp
     190:	05017403          	.insn	4, 0x05017403
     194:	0901                	addi	s2,s2,0
     196:	0000                	unimp
     198:	0518                	addi	a4,sp,640
     19a:	0905                	addi	s2,s2,1
     19c:	0000                	unimp
     19e:	0518                	addi	a4,sp,640
     1a0:	0905                	addi	s2,s2,1
     1a2:	0000                	unimp
     1a4:	0518                	addi	a4,sp,640
     1a6:	0909                	addi	s2,s2,2
     1a8:	0000                	unimp
     1aa:	1806                	slli	a6,a6,0x21
     1ac:	0905                	addi	s2,s2,1
     1ae:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     1b0:	1600                	addi	s0,sp,800
     1b2:	1805                	addi	a6,a6,-31
     1b4:	0409                	addi	s0,s0,2
     1b6:	0600                	addi	s0,sp,768
     1b8:	0518                	addi	a4,sp,640
     1ba:	0909                	addi	s2,s2,2
     1bc:	000a                	c.slli	zero,0x2
     1be:	0518                	addi	a4,sp,640
     1c0:	0909                	addi	s2,s2,2
     1c2:	0000                	unimp
     1c4:	1606                	slli	a2,a2,0x21
     1c6:	0905                	addi	s2,s2,1
     1c8:	0a09                	addi	s4,s4,2
     1ca:	0100                	addi	s0,sp,128
     1cc:	0905                	addi	s2,s2,1
     1ce:	0009                	c.nop	2
     1d0:	0600                	addi	s0,sp,768
     1d2:	0516                	slli	a0,a0,0x5
     1d4:	0909                	addi	s2,s2,2
     1d6:	0000                	unimp
     1d8:	0106                	slli	sp,sp,0x1
     1da:	1805                	addi	a6,a6,-31
     1dc:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     1de:	1800                	addi	s0,sp,48
     1e0:	0905                	addi	s2,s2,1
     1e2:	0809                	addi	a6,a6,2
     1e4:	1600                	addi	s0,sp,800
     1e6:	1805                	addi	a6,a6,-31
     1e8:	0409                	addi	s0,s0,2
     1ea:	0600                	addi	s0,sp,768
     1ec:	0518                	addi	a4,sp,640
     1ee:	0909                	addi	s2,s2,2
     1f0:	0008                	.insn	2, 0x0008
     1f2:	0518                	addi	a4,sp,640
     1f4:	0909                	addi	s2,s2,2
     1f6:	0000                	unimp
     1f8:	0106                	slli	sp,sp,0x1
     1fa:	1305                	addi	t1,t1,-31
     1fc:	0809                	addi	a6,a6,2
     1fe:	0100                	addi	s0,sp,128
     200:	1305                	addi	t1,t1,-31
     202:	0009                	c.nop	2
     204:	0600                	addi	s0,sp,768
     206:	0524                	addi	s1,sp,648
     208:	0905                	addi	s2,s2,1
     20a:	0000                	unimp
     20c:	0106                	slli	sp,sp,0x1
     20e:	0c05                	addi	s8,s8,1
     210:	0900                	addi	s0,sp,144
     212:	c202                	sw	zero,4(sp)
     214:	0000                	unimp
     216:	0012                	c.slli	zero,0x4
     218:	0000                	unimp
     21a:	0600                	addi	s0,sp,768
     21c:	0529                	addi	a0,a0,10
     21e:	00000937          	lui	s2,0x0
     222:	0518                	addi	a4,sp,640
     224:	0905                	addi	s2,s2,1 # 1 <main-0x11ffffff>
     226:	0000                	unimp
     228:	0519                	addi	a0,a0,6
     22a:	0905                	addi	s2,s2,1
     22c:	0000                	unimp
     22e:	0905051b          	addiw	a0,a0,144
     232:	0000                	unimp
     234:	0518                	addi	a4,sp,640
     236:	0905                	addi	s2,s2,1
     238:	0000                	unimp
     23a:	0519                	addi	a0,a0,6
     23c:	0905                	addi	s2,s2,1
     23e:	0000                	unimp
     240:	0d06                	slli	s10,s10,0x1
     242:	3705                	addiw	a4,a4,-31
     244:	0409                	addi	s0,s0,2
     246:	2300                	fld	fs0,0(a4)
     248:	1405                	addi	s0,s0,-31
     24a:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     24c:	1500                	addi	s0,sp,672
     24e:	0805                	addi	a6,a6,1
     250:	1009                	c.nop	-30
     252:	0600                	addi	s0,sp,768
     254:	0518                	addi	a4,sp,640
     256:	0909                	addi	s2,s2,2
     258:	0000                	unimp
     25a:	0518                	addi	a4,sp,640
     25c:	0909                	addi	s2,s2,2
     25e:	0000                	unimp
     260:	0106                	slli	sp,sp,0x1
     262:	1105                	addi	sp,sp,-31
     264:	0409                	addi	s0,s0,2
     266:	0600                	addi	s0,sp,768
     268:	051c                	addi	a5,sp,640
     26a:	0905                	addi	s2,s2,1
     26c:	0000                	unimp
     26e:	1106                	slli	sp,sp,0x21
     270:	0e05                	addi	t3,t3,1
     272:	0409                	addi	s0,s0,2
     274:	0600                	addi	s0,sp,768
     276:	0521                	addi	a0,a0,8
     278:	0905                	addi	s2,s2,1
     27a:	0000                	unimp
     27c:	0106                	slli	sp,sp,0x1
     27e:	0a05                	addi	s4,s4,1
     280:	1409                	addi	s0,s0,-30
     282:	0600                	addi	s0,sp,768
     284:	0518                	addi	a4,sp,640
     286:	0905                	addi	s2,s2,1
     288:	0000                	unimp
     28a:	0519                	addi	a0,a0,6
     28c:	0905                	addi	s2,s2,1
     28e:	0000                	unimp
     290:	0501                	addi	a0,a0,0
     292:	0914                	addi	a3,sp,144
     294:	0000                	unimp
     296:	1506                	slli	a0,a0,0x21
     298:	0b05                	addi	s6,s6,1
     29a:	0c09                	addi	s8,s8,2
     29c:	0600                	addi	s0,sp,768
     29e:	051a                	slli	a0,a0,0x6
     2a0:	0909                	addi	s2,s2,2
     2a2:	0000                	unimp
     2a4:	0106                	slli	sp,sp,0x1
     2a6:	2305                	addiw	t1,t1,1
     2a8:	0609                	addi	a2,a2,2
     2aa:	0100                	addi	s0,sp,128
     2ac:	0e05                	addi	t3,t3,1
     2ae:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     2b0:	0100                	addi	s0,sp,128
     2b2:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     2b4:	0609                	addi	a2,a2,2
     2b6:	0100                	addi	s0,sp,128
     2b8:	1a05                	addi	s4,s4,-31
     2ba:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     2bc:	0100                	addi	s0,sp,128
     2be:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     2c0:	0409                	addi	s0,s0,2
     2c2:	1800                	addi	s0,sp,48
     2c4:	1105                	addi	sp,sp,-31
     2c6:	0409                	addi	s0,s0,2
     2c8:	1600                	addi	s0,sp,800
     2ca:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     2cc:	0409                	addi	s0,s0,2
     2ce:	0600                	addi	s0,sp,768
     2d0:	0518                	addi	a4,sp,640
     2d2:	0909                	addi	s2,s2,2
     2d4:	0000                	unimp
     2d6:	0515                	addi	a0,a0,5
     2d8:	0914                	addi	a3,sp,144
     2da:	0004                	.insn	2, 0x0004
     2dc:	051c                	addi	a5,sp,640
     2de:	0905                	addi	s2,s2,1
     2e0:	0000                	unimp
     2e2:	0518                	addi	a4,sp,640
     2e4:	0905                	addi	s2,s2,1
     2e6:	0000                	unimp
     2e8:	0106                	slli	sp,sp,0x1
     2ea:	0805                	addi	a6,a6,1
     2ec:	0409                	addi	s0,s0,2
     2ee:	0600                	addi	s0,sp,768
     2f0:	0520                	addi	s0,sp,648
     2f2:	0905                	addi	s2,s2,1
     2f4:	0000                	unimp
     2f6:	0106                	slli	sp,sp,0x1
     2f8:	0805                	addi	a6,a6,1
     2fa:	0409                	addi	s0,s0,2
     2fc:	0100                	addi	s0,sp,128
     2fe:	0805                	addi	a6,a6,1
     300:	0409                	addi	s0,s0,2
     302:	0300                	addi	s0,sp,384
     304:	0140                	addi	s0,sp,132
     306:	1305                	addi	t1,t1,-31
     308:	0809                	addi	a6,a6,2
     30a:	0100                	addi	s0,sp,128
     30c:	1305                	addi	t1,t1,-31
     30e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     310:	4d00                	lw	s0,24(a0)
     312:	0b05                	addi	s6,s6,1
     314:	0a09                	addi	s4,s4,2
     316:	0000                	unimp
     318:	0402                	c.slli64	s0
     31a:	0601                	addi	a2,a2,0
     31c:	091b0523          	sb	a7,138(s6)
     320:	0000                	unimp
     322:	0106                	slli	sp,sp,0x1
     324:	2005                	.insn	2, 0x2005
     326:	0609                	addi	a2,a2,2
     328:	0000                	unimp
     32a:	0402                	c.slli64	s0
     32c:	0100                	addi	s0,sp,128
     32e:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     330:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     332:	0300                	addi	s0,sp,384
     334:	7fbe                	ld	t6,488(sp)
     336:	0501                	addi	a0,a0,0
     338:	0908                	addi	a0,sp,144
     33a:	0004                	.insn	2, 0x0004
     33c:	051a                	slli	a0,a0,0x6
     33e:	0916                	slli	s2,s2,0x5
     340:	0006                	c.slli	zero,0x1
     342:	0501                	addi	a0,a0,0
     344:	0916                	slli	s2,s2,0x5
     346:	0002                	c.slli64	zero
     348:	0501                	addi	a0,a0,0
     34a:	0912                	slli	s2,s2,0x4
     34c:	0004                	.insn	2, 0x0004
     34e:	0106                	slli	sp,sp,0x1
     350:	0505                	addi	a0,a0,1
     352:	0009                	c.nop	2
     354:	0600                	addi	s0,sp,768
     356:	0501                	addi	a0,a0,0
     358:	0916                	slli	s2,s2,0x5
     35a:	0002                	c.slli64	zero
     35c:	0200                	addi	s0,sp,256
     35e:	0304                	addi	s1,sp,384
     360:	0556                	slli	a0,a0,0x15
     362:	092e                	slli	s2,s2,0xb
     364:	0002                	c.slli64	zero
     366:	0200                	addi	s0,sp,256
     368:	0004                	.insn	2, 0x0004
     36a:	05014103          	lbu	sp,80(sp)
     36e:	0912                	slli	s2,s2,0x4
     370:	0002                	c.slli64	zero
     372:	0501                	addi	a0,a0,0
     374:	0916                	slli	s2,s2,0x5
     376:	0004                	.insn	2, 0x0004
     378:	1806                	slli	a6,a6,0x21
     37a:	0505                	addi	a0,a0,1
     37c:	0009                	c.nop	2
     37e:	1a00                	addi	s0,sp,304
     380:	0505                	addi	a0,a0,1
     382:	0009                	c.nop	2
     384:	0600                	addi	s0,sp,768
     386:	0501                	addi	a0,a0,0
     388:	0905                	addi	s2,s2,1
     38a:	0000                	unimp
     38c:	0200                	addi	s0,sp,256
     38e:	0304                	addi	s1,sp,384
     390:	5206                	lw	tp,96(sp)
     392:	2e05                	addiw	t3,t3,1
     394:	0009                	c.nop	2
     396:	0000                	unimp
     398:	0402                	c.slli64	s0
     39a:	0101                	addi	sp,sp,0
     39c:	1b05                	addi	s6,s6,-31
     39e:	0409                	addi	s0,s0,2
     3a0:	0000                	unimp
     3a2:	0402                	c.slli64	s0
     3a4:	1800                	addi	s0,sp,48
     3a6:	0d05                	addi	s10,s10,1
     3a8:	0009                	c.nop	2
     3aa:	0300                	addi	s0,sp,384
     3ac:	7fbc                	ld	a5,120(a5)
     3ae:	0501                	addi	a0,a0,0
     3b0:	0901                	addi	s2,s2,0
     3b2:	0000                	unimp
     3b4:	0518                	addi	a4,sp,640
     3b6:	0905                	addi	s2,s2,1
     3b8:	0000                	unimp
     3ba:	0518                	addi	a4,sp,640
     3bc:	0909                	addi	s2,s2,2
     3be:	0000                	unimp
     3c0:	05017403          	.insn	4, 0x05017403
     3c4:	0901                	addi	s2,s2,0
     3c6:	0000                	unimp
     3c8:	0518                	addi	a4,sp,640
     3ca:	0905                	addi	s2,s2,1
     3cc:	0000                	unimp
     3ce:	0518                	addi	a4,sp,640
     3d0:	0905                	addi	s2,s2,1
     3d2:	0000                	unimp
     3d4:	0518                	addi	a4,sp,640
     3d6:	0909                	addi	s2,s2,2
     3d8:	0000                	unimp
     3da:	0106                	slli	sp,sp,0x1
     3dc:	1805                	addi	a6,a6,-31
     3de:	0409                	addi	s0,s0,2
     3e0:	1800                	addi	s0,sp,48
     3e2:	0905                	addi	s2,s2,1
     3e4:	0809                	addi	a6,a6,2
     3e6:	1e00                	addi	s0,sp,816
     3e8:	0805                	addi	a6,a6,1
     3ea:	1009                	c.nop	-30
     3ec:	0f00                	addi	s0,sp,912
     3ee:	1805                	addi	a6,a6,-31
     3f0:	0409                	addi	s0,s0,2
     3f2:	0600                	addi	s0,sp,768
     3f4:	0518                	addi	a4,sp,640
     3f6:	0909                	addi	s2,s2,2
     3f8:	0008                	.insn	2, 0x0008
     3fa:	0518                	addi	a4,sp,640
     3fc:	0909                	addi	s2,s2,2
     3fe:	0000                	unimp
     400:	0106                	slli	sp,sp,0x1
     402:	0905                	addi	s2,s2,1
     404:	0009                	c.nop	2
     406:	0600                	addi	s0,sp,768
     408:	0520                	addi	s0,sp,648
     40a:	0905                	addi	s2,s2,1
     40c:	0000                	unimp
     40e:	0106                	slli	sp,sp,0x1
     410:	0505                	addi	a0,a0,1
     412:	0009                	c.nop	2
     414:	0600                	addi	s0,sp,768
     416:	090d0557          	.insn	4, 0x090d0557
     41a:	0000                	unimp
     41c:	017fbc03          	ld	s8,23(t6)
     420:	0105                	addi	sp,sp,1
     422:	0009                	c.nop	2
     424:	1800                	addi	s0,sp,48
     426:	0505                	addi	a0,a0,1
     428:	0009                	c.nop	2
     42a:	1a00                	addi	s0,sp,304
     42c:	0505                	addi	a0,a0,1
     42e:	0009                	c.nop	2
     430:	0600                	addi	s0,sp,768
     432:	0501                	addi	a0,a0,0
     434:	0912                	slli	s2,s2,0x4
     436:	0002                	c.slli64	zero
     438:	0501                	addi	a0,a0,0
     43a:	0916                	slli	s2,s2,0x5
     43c:	0002                	c.slli64	zero
     43e:	0200                	addi	s0,sp,256
     440:	0304                	addi	s1,sp,384
     442:	0556                	slli	a0,a0,0x15
     444:	092e                	slli	s2,s2,0xb
     446:	0002                	c.slli64	zero
     448:	0200                	addi	s0,sp,256
     44a:	0104                	addi	s1,sp,128
     44c:	0501                	addi	a0,a0,0
     44e:	0002091b          	sext.w	s2,tp
     452:	0200                	addi	s0,sp,256
     454:	0004                	.insn	2, 0x0004
     456:	05014103          	lbu	sp,80(sp)
     45a:	0912                	slli	s2,s2,0x4
     45c:	0002                	c.slli64	zero
     45e:	0501                	addi	a0,a0,0
     460:	0916                	slli	s2,s2,0x5
     462:	0004                	.insn	2, 0x0004
     464:	0501                	addi	a0,a0,0
     466:	0912                	slli	s2,s2,0x4
     468:	0002                	c.slli64	zero
     46a:	0501                	addi	a0,a0,0
     46c:	0916                	slli	s2,s2,0x5
     46e:	0004                	.insn	2, 0x0004
     470:	1806                	slli	a6,a6,0x21
     472:	0505                	addi	a0,a0,1
     474:	0009                	c.nop	2
     476:	1a00                	addi	s0,sp,304
     478:	0505                	addi	a0,a0,1
     47a:	0009                	c.nop	2
     47c:	0600                	addi	s0,sp,768
     47e:	0501                	addi	a0,a0,0
     480:	0905                	addi	s2,s2,1
     482:	0000                	unimp
     484:	0200                	addi	s0,sp,256
     486:	0304                	addi	s1,sp,384
     488:	5206                	lw	tp,96(sp)
     48a:	2e05                	addiw	t3,t3,1
     48c:	0009                	c.nop	2
     48e:	0000                	unimp
     490:	0402                	c.slli64	s0
     492:	0101                	addi	sp,sp,0
     494:	1b05                	addi	s6,s6,-31
     496:	0009                	c.nop	2
     498:	0000                	unimp
     49a:	0402                	c.slli64	s0
     49c:	05010603          	lb	a2,80(sp)
     4a0:	092e                	slli	s2,s2,0xb
     4a2:	0004                	.insn	2, 0x0004
     4a4:	0200                	addi	s0,sp,256
     4a6:	0104                	addi	s1,sp,128
     4a8:	0501                	addi	a0,a0,0
     4aa:	0004091b          	sext.w	s2,s0
     4ae:	0200                	addi	s0,sp,256
     4b0:	0004                	.insn	2, 0x0004
     4b2:	05014103          	lbu	sp,80(sp)
     4b6:	0912                	slli	s2,s2,0x4
     4b8:	0002                	c.slli64	zero
     4ba:	0200                	addi	s0,sp,256
     4bc:	0104                	addi	s1,sp,128
     4be:	0556                	slli	a0,a0,0x15
     4c0:	0004091b          	sext.w	s2,s0
     4c4:	0200                	addi	s0,sp,256
     4c6:	0004                	.insn	2, 0x0004
     4c8:	05014103          	lbu	sp,80(sp)
     4cc:	0912                	slli	s2,s2,0x4
     4ce:	0002                	c.slli64	zero
     4d0:	0501                	addi	a0,a0,0
     4d2:	0916                	slli	s2,s2,0x5
     4d4:	0004                	.insn	2, 0x0004
     4d6:	1806                	slli	a6,a6,0x21
     4d8:	0505                	addi	a0,a0,1
     4da:	0009                	c.nop	2
     4dc:	1a00                	addi	s0,sp,304
     4de:	0505                	addi	a0,a0,1
     4e0:	0009                	c.nop	2
     4e2:	0600                	addi	s0,sp,768
     4e4:	0501                	addi	a0,a0,0
     4e6:	0905                	addi	s2,s2,1
     4e8:	0000                	unimp
     4ea:	0200                	addi	s0,sp,256
     4ec:	0304                	addi	s1,sp,384
     4ee:	5206                	lw	tp,96(sp)
     4f0:	2e05                	addiw	t3,t3,1
     4f2:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     4f4:	0000                	unimp
     4f6:	0402                	c.slli64	s0
     4f8:	0101                	addi	sp,sp,0
     4fa:	1b05                	addi	s6,s6,-31
     4fc:	0a09                	addi	s4,s4,2
     4fe:	0600                	addi	s0,sp,768
     500:	0501                	addi	a0,a0,0
     502:	0008091b          	sext.w	s2,a6
     506:	0501                	addi	a0,a0,0
     508:	0000091b          	sext.w	s2,zero
     50c:	0200                	addi	s0,sp,256
     50e:	0004                	.insn	2, 0x0004
     510:	1d06                	slli	s10,s10,0x21
     512:	0905                	addi	s2,s2,1
     514:	0009                	c.nop	2
     516:	0600                	addi	s0,sp,768
     518:	0501                	addi	a0,a0,0
     51a:	0918                	addi	a4,sp,144
     51c:	0008                	.insn	2, 0x0008
     51e:	0200                	addi	s0,sp,256
     520:	0104                	addi	s1,sp,128
     522:	0516                	slli	a0,a0,0x5
     524:	0919                	addi	s2,s2,6
     526:	0002                	c.slli64	zero
     528:	0200                	addi	s0,sp,256
     52a:	0004                	.insn	2, 0x0004
     52c:	0518                	addi	a4,sp,640
     52e:	0918                	addi	a4,sp,144
     530:	0008                	.insn	2, 0x0008
     532:	0200                	addi	s0,sp,256
     534:	0304                	addi	s1,sp,384
     536:	1606                	slli	a2,a2,0x21
     538:	1f05                	addi	t5,t5,-31
     53a:	0009                	c.nop	2
     53c:	0000                	unimp
     53e:	0402                	c.slli64	s0
     540:	0101                	addi	sp,sp,0
     542:	1905                	addi	s2,s2,-31
     544:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     546:	0000                	unimp
     548:	0402                	c.slli64	s0
     54a:	1b00                	addi	s0,sp,432
     54c:	0505                	addi	a0,a0,1
     54e:	0009                	c.nop	2
     550:	0600                	addi	s0,sp,768
     552:	0501                	addi	a0,a0,0
     554:	090c                	addi	a1,sp,144
     556:	0002                	c.slli64	zero
     558:	0518                	addi	a4,sp,640
     55a:	0901                	addi	s2,s2,0
     55c:	0002                	c.slli64	zero
     55e:	0516                	slli	a0,a0,0x5
     560:	090c                	addi	a1,sp,144
     562:	000e                	c.slli	zero,0x3
     564:	0501                	addi	a0,a0,0
     566:	090c                	addi	a1,sp,144
     568:	0004                	.insn	2, 0x0004
     56a:	0518                	addi	a4,sp,640
     56c:	0901                	addi	s2,s2,0
     56e:	0004                	.insn	2, 0x0004
     570:	0306                	slli	t1,t1,0x1
     572:	0905015b          	.insn	4, 0x0905015b
     576:	0009                	c.nop	2
     578:	1a00                	addi	s0,sp,304
     57a:	0505                	addi	a0,a0,1
     57c:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     57e:	0600                	addi	s0,sp,768
     580:	0501                	addi	a0,a0,0
     582:	0908                	addi	a0,sp,144
     584:	000c                	.insn	2, 0x000c
     586:	0528                	addi	a0,sp,648
     588:	0909                	addi	s2,s2,2
     58a:	0004                	.insn	2, 0x0004
     58c:	1406                	slli	s0,s0,0x21
     58e:	0905                	addi	s2,s2,1
     590:	0009                	c.nop	2
     592:	0600                	addi	s0,sp,768
     594:	05014803          	lbu	a6,80(sp)
     598:	00080913          	mv	s2,a6
     59c:	0501                	addi	a0,a0,0
     59e:	00020913          	mv	s2,tp
     5a2:	0501                	addi	a0,a0,0
     5a4:	0908                	addi	a0,sp,144
     5a6:	0004                	.insn	2, 0x0004
     5a8:	0912054f          	fnmadd.s	fa0,ft4,fa7,ft1,rne
     5ac:	0004                	.insn	2, 0x0004
     5ae:	1a06                	slli	s4,s4,0x21
     5b0:	0505                	addi	a0,a0,1
     5b2:	0009                	c.nop	2
     5b4:	1800                	addi	s0,sp,48
     5b6:	0505                	addi	a0,a0,1
     5b8:	0009                	c.nop	2
     5ba:	1800                	addi	s0,sp,48
     5bc:	0905                	addi	s2,s2,1
     5be:	0009                	c.nop	2
     5c0:	0300                	addi	s0,sp,384
     5c2:	0142                	slli	sp,sp,0x10
     5c4:	0105                	addi	sp,sp,1
     5c6:	0009                	c.nop	2
     5c8:	1800                	addi	s0,sp,48
     5ca:	0505                	addi	a0,a0,1
     5cc:	0009                	c.nop	2
     5ce:	0600                	addi	s0,sp,768
     5d0:	0501                	addi	a0,a0,0
     5d2:	0908                	addi	a0,sp,144
     5d4:	0004                	.insn	2, 0x0004
     5d6:	051a                	slli	a0,a0,0x6
     5d8:	0912                	slli	s2,s2,0x4
     5da:	000c                	.insn	2, 0x000c
     5dc:	0106                	slli	sp,sp,0x1
     5de:	0505                	addi	a0,a0,1
     5e0:	0009                	c.nop	2
     5e2:	0600                	addi	s0,sp,768
     5e4:	0501                	addi	a0,a0,0
     5e6:	0916                	slli	s2,s2,0x5
     5e8:	000a                	c.slli	zero,0x2
     5ea:	1806                	slli	a6,a6,0x21
     5ec:	0505                	addi	a0,a0,1
     5ee:	0009                	c.nop	2
     5f0:	1a00                	addi	s0,sp,304
     5f2:	0505                	addi	a0,a0,1
     5f4:	0009                	c.nop	2
     5f6:	0600                	addi	s0,sp,768
     5f8:	0501                	addi	a0,a0,0
     5fa:	0905                	addi	s2,s2,1
     5fc:	0000                	unimp
     5fe:	5006                	.insn	2, 0x5006
     600:	0505                	addi	a0,a0,1
     602:	0009                	c.nop	2
     604:	0600                	addi	s0,sp,768
     606:	05014303          	lbu	t1,80(sp)
     60a:	0912                	slli	s2,s2,0x4
     60c:	0002                	c.slli64	zero
     60e:	0554                	addi	a3,sp,644
     610:	0908                	addi	a0,sp,144
     612:	000e                	c.slli	zero,0x3
     614:	0501                	addi	a0,a0,0
     616:	0908                	addi	a0,sp,144
     618:	0000                	unimp
     61a:	0200                	addi	s0,sp,256
     61c:	0104                	addi	s1,sp,128
     61e:	1e06                	slli	t3,t3,0x21
     620:	1905                	addi	s2,s2,-31
     622:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     624:	0600                	addi	s0,sp,768
     626:	0501                	addi	a0,a0,0
     628:	0919                	addi	s2,s2,6
     62a:	0000                	unimp
     62c:	0200                	addi	s0,sp,256
     62e:	0004                	.insn	2, 0x0004
     630:	0306                	slli	t1,t1,0x1
     632:	0164                	addi	s1,sp,140
     634:	0905                	addi	s2,s2,1
     636:	0009                	c.nop	2
     638:	0300                	addi	s0,sp,384
     63a:	0154                	addi	a3,sp,132
     63c:	0105                	addi	sp,sp,1
     63e:	0009                	c.nop	2
     640:	1800                	addi	s0,sp,48
     642:	0505                	addi	a0,a0,1
     644:	0009                	c.nop	2
     646:	0600                	addi	s0,sp,768
     648:	0501                	addi	a0,a0,0
     64a:	00080913          	mv	s2,a6
     64e:	0501                	addi	a0,a0,0
     650:	0908                	addi	a0,sp,144
     652:	0008                	.insn	2, 0x0008
     654:	051a                	slli	a0,a0,0x6
     656:	0912                	slli	s2,s2,0x4
     658:	0004                	.insn	2, 0x0004
     65a:	0501                	addi	a0,a0,0
     65c:	0912                	slli	s2,s2,0x4
     65e:	0008                	.insn	2, 0x0008
     660:	0106                	slli	sp,sp,0x1
     662:	0505                	addi	a0,a0,1
     664:	0009                	c.nop	2
     666:	0600                	addi	s0,sp,768
     668:	0501                	addi	a0,a0,0
     66a:	0916                	slli	s2,s2,0x5
     66c:	000a                	c.slli	zero,0x2
     66e:	1806                	slli	a6,a6,0x21
     670:	0505                	addi	a0,a0,1
     672:	0009                	c.nop	2
     674:	1a00                	addi	s0,sp,304
     676:	0505                	addi	a0,a0,1
     678:	0009                	c.nop	2
     67a:	0600                	addi	s0,sp,768
     67c:	0501                	addi	a0,a0,0
     67e:	0905                	addi	s2,s2,1
     680:	0000                	unimp
     682:	055c                	addi	a5,sp,644
     684:	0901                	addi	s2,s2,0
     686:	0002                	c.slli64	zero
     688:	017fb703          	ld	a4,23(t6)
     68c:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     68e:	0809                	addi	a6,a6,2
     690:	3f00                	fld	fs0,56(a4)
     692:	1005                	c.nop	-31
     694:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     696:	3800                	fld	fs0,48(s0)
     698:	0105                	addi	sp,sp,1
     69a:	0409                	addi	s0,s0,2
     69c:	0300                	addi	s0,sp,384
     69e:	7fac                	ld	a1,120(a5)
     6a0:	0501                	addi	a0,a0,0
     6a2:	0918                	addi	a4,sp,144
     6a4:	0008                	.insn	2, 0x0008
     6a6:	0501                	addi	a0,a0,0
     6a8:	0918                	addi	a4,sp,144
     6aa:	0002                	c.slli64	zero
     6ac:	0518                	addi	a4,sp,640
     6ae:	0909                	addi	s2,s2,2
     6b0:	0008                	.insn	2, 0x0008
     6b2:	1f06                	slli	t5,t5,0x21
     6b4:	0905                	addi	s2,s2,1
     6b6:	0009                	c.nop	2
     6b8:	0300                	addi	s0,sp,384
     6ba:	0174                	addi	a3,sp,140
     6bc:	0105                	addi	sp,sp,1
     6be:	0009                	c.nop	2
     6c0:	1800                	addi	s0,sp,48
     6c2:	0505                	addi	a0,a0,1
     6c4:	0009                	c.nop	2
     6c6:	1800                	addi	s0,sp,48
     6c8:	0505                	addi	a0,a0,1
     6ca:	0009                	c.nop	2
     6cc:	1800                	addi	s0,sp,48
     6ce:	0905                	addi	s2,s2,1
     6d0:	0009                	c.nop	2
     6d2:	0600                	addi	s0,sp,768
     6d4:	0501                	addi	a0,a0,0
     6d6:	0918                	addi	a4,sp,144
     6d8:	0004                	.insn	2, 0x0004
     6da:	1806                	slli	a6,a6,0x21
     6dc:	0905                	addi	s2,s2,1
     6de:	0a09                	addi	s4,s4,2
     6e0:	1800                	addi	s0,sp,48
     6e2:	0905                	addi	s2,s2,1
     6e4:	0009                	c.nop	2
     6e6:	0600                	addi	s0,sp,768
     6e8:	0516                	slli	a0,a0,0x5
     6ea:	0909                	addi	s2,s2,2
     6ec:	000e                	c.slli	zero,0x3
     6ee:	0501                	addi	a0,a0,0
     6f0:	0909                	addi	s2,s2,2
     6f2:	0000                	unimp
     6f4:	1f06                	slli	t5,t5,0x21
     6f6:	0905                	addi	s2,s2,1
     6f8:	0009                	c.nop	2
     6fa:	0300                	addi	s0,sp,384
     6fc:	0174                	addi	a3,sp,140
     6fe:	0105                	addi	sp,sp,1
     700:	0009                	c.nop	2
     702:	1800                	addi	s0,sp,48
     704:	0505                	addi	a0,a0,1
     706:	0009                	c.nop	2
     708:	1800                	addi	s0,sp,48
     70a:	0505                	addi	a0,a0,1
     70c:	0009                	c.nop	2
     70e:	1800                	addi	s0,sp,48
     710:	0905                	addi	s2,s2,1
     712:	0009                	c.nop	2
     714:	0600                	addi	s0,sp,768
     716:	0501                	addi	a0,a0,0
     718:	0918                	addi	a4,sp,144
     71a:	0008                	.insn	2, 0x0008
     71c:	0501                	addi	a0,a0,0
     71e:	0918                	addi	a4,sp,144
     720:	0002                	c.slli64	zero
     722:	0518                	addi	a4,sp,640
     724:	0909                	addi	s2,s2,2
     726:	0002                	c.slli64	zero
     728:	0516                	slli	a0,a0,0x5
     72a:	0918                	addi	a4,sp,144
     72c:	0004                	.insn	2, 0x0004
     72e:	1806                	slli	a6,a6,0x21
     730:	0905                	addi	s2,s2,1
     732:	0a09                	addi	s4,s4,2
     734:	1800                	addi	s0,sp,48
     736:	0905                	addi	s2,s2,1
     738:	0009                	c.nop	2
     73a:	0600                	addi	s0,sp,768
     73c:	0516                	slli	a0,a0,0x5
     73e:	0009                	c.nop	2
     740:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     742:	02ce                	slli	t0,t0,0x13
     744:	1200                	addi	s0,sp,288
     746:	0000                	unimp
     748:	0000                	unimp
     74a:	6d06                	ld	s10,64(sp)
     74c:	2705                	addiw	a4,a4,1
     74e:	0009                	c.nop	2
     750:	1b00                	addi	s0,sp,432
     752:	0505                	addi	a0,a0,1
     754:	0009                	c.nop	2
     756:	1800                	addi	s0,sp,48
     758:	0505                	addi	a0,a0,1
     75a:	0009                	c.nop	2
     75c:	0100                	addi	s0,sp,128
     75e:	0a05                	addi	s4,s4,1
     760:	0009                	c.nop	2
     762:	0000                	unimp
     764:	0402                	c.slli64	s0
     766:	0101                	addi	sp,sp,0
     768:	1705                	addi	a4,a4,-31
     76a:	0009                	c.nop	2
     76c:	0000                	unimp
     76e:	0402                	c.slli64	s0
     770:	0600                	addi	s0,sp,768
     772:	0512                	slli	a0,a0,0x4
     774:	000c0927          	.insn	4, 0x000c0927
     778:	0200                	addi	s0,sp,256
     77a:	0104                	addi	s1,sp,128
     77c:	051c                	addi	a5,sp,640
     77e:	091a                	slli	s2,s2,0x6
     780:	0004                	.insn	2, 0x0004
     782:	0501                	addi	a0,a0,0
     784:	00120917          	auipc	s2,0x120
     788:	0200                	addi	s0,sp,256
     78a:	0004                	.insn	2, 0x0004
     78c:	0501                	addi	a0,a0,0
     78e:	0910                	addi	a2,sp,144
     790:	0002                	c.slli64	zero
     792:	0516                	slli	a0,a0,0x5
     794:	000a090b          	.insn	4, 0x000a090b
     798:	0519                	addi	a0,a0,6
     79a:	090c                	addi	a1,sp,144
     79c:	0004                	.insn	2, 0x0004
     79e:	0519                	addi	a0,a0,6
     7a0:	090d                	addi	s2,s2,3 # 120787 <main-0x11edf879>
     7a2:	000a                	c.slli	zero,0x2
     7a4:	1506                	slli	a0,a0,0x21
     7a6:	0905                	addi	s2,s2,1
     7a8:	0009                	c.nop	2
     7aa:	0600                	addi	s0,sp,768
     7ac:	0501                	addi	a0,a0,0
     7ae:	090c                	addi	a1,sp,144
     7b0:	0004                	.insn	2, 0x0004
     7b2:	0518                	addi	a4,sp,640
     7b4:	090e                	slli	s2,s2,0x3
     7b6:	0004                	.insn	2, 0x0004
     7b8:	0106                	slli	sp,sp,0x1
     7ba:	0d05                	addi	s10,s10,1
     7bc:	0009                	c.nop	2
     7be:	1800                	addi	s0,sp,48
     7c0:	0d05                	addi	s10,s10,1
     7c2:	0009                	c.nop	2
     7c4:	0600                	addi	s0,sp,768
     7c6:	0501                	addi	a0,a0,0
     7c8:	0918                	addi	a4,sp,144
     7ca:	0008                	.insn	2, 0x0008
     7cc:	0501                	addi	a0,a0,0
     7ce:	090d                	addi	s2,s2,3
     7d0:	001a                	c.slli	zero,0x6
     7d2:	5906                	lw	s2,96(sp)
     7d4:	0d05                	addi	s10,s10,1
     7d6:	0009                	c.nop	2
     7d8:	0600                	addi	s0,sp,768
     7da:	0501                	addi	a0,a0,0
     7dc:	0918                	addi	a4,sp,144
     7de:	0008                	.insn	2, 0x0008
     7e0:	0200                	addi	s0,sp,256
     7e2:	0104                	addi	s1,sp,128
     7e4:	0501                	addi	a0,a0,0
     7e6:	0915                	addi	s2,s2,5
     7e8:	0002                	c.slli64	zero
     7ea:	0200                	addi	s0,sp,256
     7ec:	0204                	addi	s1,sp,256
     7ee:	0306                	slli	t1,t1,0x1
     7f0:	05017fbb          	.insn	4, 0x05017fbb
     7f4:	0920                	addi	s0,sp,152
     7f6:	0002                	c.slli64	zero
     7f8:	0200                	addi	s0,sp,256
     7fa:	0104                	addi	s1,sp,128
     7fc:	0501                	addi	a0,a0,0
     7fe:	00000917          	auipc	s2,0x0
     802:	0106                	slli	sp,sp,0x1
     804:	1a05                	addi	s4,s4,-31
     806:	0809                	addi	a6,a6,2
     808:	0100                	addi	s0,sp,128
     80a:	1705                	addi	a4,a4,-31
     80c:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     80e:	0100                	addi	s0,sp,128
     810:	1705                	addi	a4,a4,-31
     812:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     814:	0100                	addi	s0,sp,128
     816:	1705                	addi	a4,a4,-31
     818:	0a09                	addi	s4,s4,2
     81a:	0100                	addi	s0,sp,128
     81c:	1705                	addi	a4,a4,-31
     81e:	0009                	c.nop	2
     820:	0000                	unimp
     822:	0402                	c.slli64	s0
     824:	0600                	addi	s0,sp,768
     826:	055f 0905 0000      	.insn	6, 0x0905055f
     82c:	017ed903          	lhu	s2,23(t4)
     830:	0105                	addi	sp,sp,1
     832:	0009                	c.nop	2
     834:	1800                	addi	s0,sp,48
     836:	0505                	addi	a0,a0,1
     838:	0009                	c.nop	2
     83a:	0600                	addi	s0,sp,768
     83c:	0501                	addi	a0,a0,0
     83e:	0004090b          	.insn	4, 0x0004090b
     842:	1806                	slli	a6,a6,0x21
     844:	0505                	addi	a0,a0,1
     846:	0009                	c.nop	2
     848:	0600                	addi	s0,sp,768
     84a:	0501                	addi	a0,a0,0
     84c:	0908                	addi	a0,sp,144
     84e:	0004                	.insn	2, 0x0004
     850:	05be                	slli	a1,a1,0xf
     852:	0901                	addi	s2,s2,0 # 7fe <main-0x11fff802>
     854:	0008                	.insn	2, 0x0008
     856:	0501                	addi	a0,a0,0
     858:	0901                	addi	s2,s2,0
     85a:	0006                	c.slli	zero,0x1
     85c:	0d06                	slli	s10,s10,0x1
     85e:	1505                	addi	a0,a0,-31
     860:	1009                	c.nop	-30
     862:	0600                	addi	s0,sp,768
     864:	05014203          	lbu	tp,80(sp)
     868:	090e                	slli	s2,s2,0x3
     86a:	0004                	.insn	2, 0x0004
     86c:	3206                	fld	ft4,96(sp)
     86e:	1505                	addi	a0,a0,-31
     870:	0009                	c.nop	2
     872:	1800                	addi	s0,sp,48
     874:	1505                	addi	a0,a0,-31
     876:	0009                	c.nop	2
     878:	0600                	addi	s0,sp,768
     87a:	0501                	addi	a0,a0,0
     87c:	0920                	addi	s0,sp,152
     87e:	0012                	c.slli	zero,0x4
     880:	0516                	slli	a0,a0,0x5
     882:	0924                	addi	s1,sp,152
     884:	0002                	c.slli64	zero
     886:	0501                	addi	a0,a0,0
     888:	0924                	addi	s1,sp,152
     88a:	0000                	unimp
     88c:	05016503          	lwu	a0,80(sp)
     890:	090e                	slli	s2,s2,0x3
     892:	0002                	c.slli64	zero
     894:	0200                	addi	s0,sp,256
     896:	0104                	addi	s1,sp,128
     898:	091d0533          	.insn	4, 0x091d0533
     89c:	0002                	c.slli64	zero
     89e:	0200                	addi	s0,sp,256
     8a0:	0004                	.insn	2, 0x0004
     8a2:	1806                	slli	a6,a6,0x21
     8a4:	1505                	addi	a0,a0,-31
     8a6:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     8a8:	0600                	addi	s0,sp,768
     8aa:	0501                	addi	a0,a0,0
     8ac:	0915                	addi	s2,s2,5
     8ae:	0002                	c.slli64	zero
     8b0:	2406                	fld	fs0,64(sp)
     8b2:	1505                	addi	a0,a0,-31
     8b4:	0009                	c.nop	2
     8b6:	0600                	addi	s0,sp,768
     8b8:	0501                	addi	a0,a0,0
     8ba:	0921                	addi	s2,s2,8
     8bc:	0006                	c.slli	zero,0x1
     8be:	1806                	slli	a6,a6,0x21
     8c0:	1505                	addi	a0,a0,-31
     8c2:	0009                	c.nop	2
     8c4:	0300                	addi	s0,sp,384
     8c6:	7f8a                	ld	t6,160(sp)
     8c8:	0501                	addi	a0,a0,0
     8ca:	0901                	addi	s2,s2,0
     8cc:	0000                	unimp
     8ce:	0518                	addi	a4,sp,640
     8d0:	0905                	addi	s2,s2,1
     8d2:	0000                	unimp
     8d4:	0106                	slli	sp,sp,0x1
     8d6:	0805                	addi	a6,a6,1
     8d8:	0409                	addi	s0,s0,2
     8da:	1800                	addi	s0,sp,48
     8dc:	1005                	c.nop	-31
     8de:	0809                	addi	a6,a6,2
     8e0:	1b00                	addi	s0,sp,432
     8e2:	0e05                	addi	t3,t3,1
     8e4:	0609                	addi	a2,a2,2
     8e6:	0600                	addi	s0,sp,768
     8e8:	0518                	addi	a4,sp,640
     8ea:	0909                	addi	s2,s2,2
     8ec:	0008                	.insn	2, 0x0008
     8ee:	0518                	addi	a4,sp,640
     8f0:	0909                	addi	s2,s2,2
     8f2:	0000                	unimp
     8f4:	0106                	slli	sp,sp,0x1
     8f6:	0c05                	addi	s8,s8,1
     8f8:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     8fa:	0600                	addi	s0,sp,768
     8fc:	0515                	addi	a0,a0,5
     8fe:	0000090b          	.insn	4, 0x090b
     902:	0106                	slli	sp,sp,0x1
     904:	0e05                	addi	t3,t3,1
     906:	0809                	addi	a6,a6,2
     908:	0100                	addi	s0,sp,128
     90a:	0b05                	addi	s6,s6,1
     90c:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     90e:	0100                	addi	s0,sp,128
     910:	0b05                	addi	s6,s6,1
     912:	0009                	c.nop	2
     914:	0000                	unimp
     916:	0402                	c.slli64	s0
     918:	8701                	c.srai64	a4
     91a:	1d05                	addi	s10,s10,-31
     91c:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     91e:	0000                	unimp
     920:	0402                	c.slli64	s0
     922:	0600                	addi	s0,sp,768
     924:	0518                	addi	a4,sp,640
     926:	0915                	addi	s2,s2,5
     928:	0002                	c.slli64	zero
     92a:	0306                	slli	t1,t1,0x1
     92c:	0154                	addi	a3,sp,132
     92e:	0e05                	addi	t3,t3,1
     930:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     932:	4300                	lw	s0,0(a4)
     934:	1505                	addi	a0,a0,-31
     936:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     938:	0100                	addi	s0,sp,128
     93a:	1505                	addi	a0,a0,-31
     93c:	0009                	c.nop	2
     93e:	0600                	addi	s0,sp,768
     940:	051f 0915 0000      	.insn	6, 0x0915051f
     946:	0306                	slli	t1,t1,0x1
     948:	7f88                	ld	a0,56(a5)
     94a:	0501                	addi	a0,a0,0
     94c:	0909                	addi	s2,s2,2
     94e:	0004                	.insn	2, 0x0004
     950:	091b058f          	.insn	4, 0x091b058f
     954:	0004                	.insn	2, 0x0004
     956:	1806                	slli	a6,a6,0x21
     958:	1505                	addi	a0,a0,-31
     95a:	0009                	c.nop	2
     95c:	0300                	addi	s0,sp,384
     95e:	7f80                	ld	s0,56(a5)
     960:	0501                	addi	a0,a0,0
     962:	0901                	addi	s2,s2,0
     964:	0000                	unimp
     966:	0518                	addi	a4,sp,640
     968:	0905                	addi	s2,s2,1
     96a:	0000                	unimp
     96c:	051c                	addi	a5,sp,640
     96e:	0000090b          	.insn	4, 0x090b
     972:	0518                	addi	a4,sp,640
     974:	0909                	addi	s2,s2,2
     976:	0008                	.insn	2, 0x0008
     978:	0518                	addi	a4,sp,640
     97a:	0909                	addi	s2,s2,2
     97c:	0000                	unimp
     97e:	0515                	addi	a0,a0,5
     980:	0000090b          	.insn	4, 0x090b
     984:	0518                	addi	a4,sp,640
     986:	0909                	addi	s2,s2,2
     988:	000c                	.insn	2, 0x000c
     98a:	0518                	addi	a4,sp,640
     98c:	0909                	addi	s2,s2,2
     98e:	0000                	unimp
     990:	0515                	addi	a0,a0,5
     992:	0000090b          	.insn	4, 0x090b
     996:	0106                	slli	sp,sp,0x1
     998:	0b05                	addi	s6,s6,1
     99a:	0009                	c.nop	2
     99c:	0600                	addi	s0,sp,768
     99e:	0592                	slli	a1,a1,0x4
     9a0:	0915                	addi	s2,s2,5
     9a2:	0000                	unimp
     9a4:	0106                	slli	sp,sp,0x1
     9a6:	2005                	.insn	2, 0x2005
     9a8:	1009                	c.nop	-30
     9aa:	0000                	unimp
     9ac:	0402                	c.slli64	s0
     9ae:	1601                	addi	a2,a2,-32
     9b0:	1d05                	addi	s10,s10,-31
     9b2:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     9b4:	0000                	unimp
     9b6:	0402                	c.slli64	s0
     9b8:	1600                	addi	s0,sp,800
     9ba:	1b05                	addi	s6,s6,-31
     9bc:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     9be:	0100                	addi	s0,sp,128
     9c0:	1b05                	addi	s6,s6,-31
     9c2:	0009                	c.nop	2
     9c4:	0300                	addi	s0,sp,384
     9c6:	014c                	addi	a1,sp,132
     9c8:	0e05                	addi	t3,t3,1
     9ca:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     9cc:	0000                	unimp
     9ce:	0402                	c.slli64	s0
     9d0:	4d01                	li	s10,0
     9d2:	1d05                	addi	s10,s10,-31
     9d4:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     9d6:	0000                	unimp
     9d8:	0402                	c.slli64	s0
     9da:	0600                	addi	s0,sp,768
     9dc:	0518                	addi	a4,sp,640
     9de:	0915                	addi	s2,s2,5
     9e0:	0002                	c.slli64	zero
     9e2:	0106                	slli	sp,sp,0x1
     9e4:	1505                	addi	a0,a0,-31
     9e6:	0009                	c.nop	2
     9e8:	0600                	addi	s0,sp,768
     9ea:	05016e03          	lwu	t3,80(sp)
     9ee:	0915                	addi	s2,s2,5
     9f0:	0000                	unimp
     9f2:	0518                	addi	a4,sp,640
     9f4:	0915                	addi	s2,s2,5
     9f6:	0000                	unimp
     9f8:	0106                	slli	sp,sp,0x1
     9fa:	2005                	.insn	2, 0x2005
     9fc:	1209                	addi	tp,tp,-30 # ffffffffffffffe2 <__sheap+0xffffffffedffcfe2>
     9fe:	1600                	addi	s0,sp,800
     a00:	2405                	addiw	s0,s0,1
     a02:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     a04:	0100                	addi	s0,sp,128
     a06:	2405                	addiw	s0,s0,1
     a08:	0009                	c.nop	2
     a0a:	0300                	addi	s0,sp,384
     a0c:	0e05015b          	.insn	4, 0x0e05015b
     a10:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     a12:	0000                	unimp
     a14:	0402                	c.slli64	s0
     a16:	3d01                	addiw	s10,s10,-32
     a18:	1d05                	addi	s10,s10,-31
     a1a:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     a1c:	0000                	unimp
     a1e:	0402                	c.slli64	s0
     a20:	0600                	addi	s0,sp,768
     a22:	0518                	addi	a4,sp,640
     a24:	0915                	addi	s2,s2,5
     a26:	0002                	c.slli64	zero
     a28:	0106                	slli	sp,sp,0x1
     a2a:	1505                	addi	a0,a0,-31
     a2c:	0009                	c.nop	2
     a2e:	0600                	addi	s0,sp,768
     a30:	05015c03          	lhu	s8,80(sp)
     a34:	0915                	addi	s2,s2,5
     a36:	0000                	unimp
     a38:	0106                	slli	sp,sp,0x1
     a3a:	1605                	addi	a2,a2,-31
     a3c:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     a3e:	0600                	addi	s0,sp,768
     a40:	0518                	addi	a4,sp,640
     a42:	0915                	addi	s2,s2,5
     a44:	0000                	unimp
     a46:	0106                	slli	sp,sp,0x1
     a48:	1c05                	addi	s8,s8,-31
     a4a:	0809                	addi	a6,a6,2
     a4c:	0100                	addi	s0,sp,128
     a4e:	1805                	addi	a6,a6,-31
     a50:	0809                	addi	a6,a6,2
     a52:	0600                	addi	s0,sp,768
     a54:	051a                	slli	a0,a0,0x6
     a56:	091c                	addi	a5,sp,144
     a58:	0000                	unimp
     a5a:	0106                	slli	sp,sp,0x1
     a5c:	1f05                	addi	t5,t5,-31
     a5e:	0809                	addi	a6,a6,2
     a60:	0600                	addi	s0,sp,768
     a62:	051a                	slli	a0,a0,0x6
     a64:	091c                	addi	a5,sp,144
     a66:	0000                	unimp
     a68:	0106                	slli	sp,sp,0x1
     a6a:	1f05                	addi	t5,t5,-31
     a6c:	0809                	addi	a6,a6,2
     a6e:	0600                	addi	s0,sp,768
     a70:	051a                	slli	a0,a0,0x6
     a72:	091c                	addi	a5,sp,144
     a74:	0000                	unimp
     a76:	0106                	slli	sp,sp,0x1
     a78:	1f05                	addi	t5,t5,-31
     a7a:	0809                	addi	a6,a6,2
     a7c:	0600                	addi	s0,sp,768
     a7e:	0919051b          	addiw	a0,s2,145
     a82:	0012                	c.slli	zero,0x4
     a84:	051c                	addi	a5,sp,640
     a86:	0915                	addi	s2,s2,5
     a88:	0000                	unimp
     a8a:	0518                	addi	a4,sp,640
     a8c:	0915                	addi	s2,s2,5
     a8e:	0000                	unimp
     a90:	0106                	slli	sp,sp,0x1
     a92:	2005                	.insn	2, 0x2005
     a94:	0409                	addi	s0,s0,2
     a96:	0100                	addi	s0,sp,128
     a98:	2005                	.insn	2, 0x2005
     a9a:	0e09                	addi	t3,t3,2
     a9c:	1600                	addi	s0,sp,800
     a9e:	2405                	addiw	s0,s0,1
     aa0:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     aa2:	0100                	addi	s0,sp,128
     aa4:	2405                	addiw	s0,s0,1
     aa6:	0009                	c.nop	2
     aa8:	0300                	addi	s0,sp,384
     aaa:	016a                	slli	sp,sp,0x1a
     aac:	0e05                	addi	t3,t3,1
     aae:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     ab0:	0000                	unimp
     ab2:	0402                	c.slli64	s0
     ab4:	2e01                	sext.w	t3,t3
     ab6:	1d05                	addi	s10,s10,-31
     ab8:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     aba:	0000                	unimp
     abc:	0402                	c.slli64	s0
     abe:	0600                	addi	s0,sp,768
     ac0:	0518                	addi	a4,sp,640
     ac2:	0915                	addi	s2,s2,5
     ac4:	0002                	c.slli64	zero
     ac6:	0106                	slli	sp,sp,0x1
     ac8:	1505                	addi	a0,a0,-31
     aca:	0009                	c.nop	2
     acc:	0600                	addi	s0,sp,768
     ace:	052e                	slli	a0,a0,0xb
     ad0:	0915                	addi	s2,s2,5
     ad2:	0000                	unimp
     ad4:	0518                	addi	a4,sp,640
     ad6:	0915                	addi	s2,s2,5
     ad8:	0000                	unimp
     ada:	0106                	slli	sp,sp,0x1
     adc:	2005                	.insn	2, 0x2005
     ade:	0409                	addi	s0,s0,2
     ae0:	0000                	unimp
     ae2:	0402                	c.slli64	s0
     ae4:	0101                	addi	sp,sp,0
     ae6:	1d05                	addi	s10,s10,-31
     ae8:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     aea:	0000                	unimp
     aec:	0402                	c.slli64	s0
     aee:	1600                	addi	s0,sp,800
     af0:	2405                	addiw	s0,s0,1
     af2:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     af4:	1800                	addi	s0,sp,48
     af6:	2005                	.insn	2, 0x2005
     af8:	0809                	addi	a6,a6,2
     afa:	0600                	addi	s0,sp,768
     afc:	0518                	addi	a4,sp,640
     afe:	0915                	addi	s2,s2,5
     b00:	0000                	unimp
     b02:	0306                	slli	t1,t1,0x1
     b04:	0e05014f          	.insn	4, 0x0e05014f
     b08:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     b0a:	4800                	lw	s0,16(s0)
     b0c:	1505                	addi	a0,a0,-31
     b0e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     b10:	0100                	addi	s0,sp,128
     b12:	1505                	addi	a0,a0,-31
     b14:	0009                	c.nop	2
     b16:	0600                	addi	s0,sp,768
     b18:	05016f03          	lwu	t5,80(sp)
     b1c:	0915                	addi	s2,s2,5
     b1e:	0000                	unimp
     b20:	0518                	addi	a4,sp,640
     b22:	0915                	addi	s2,s2,5
     b24:	0000                	unimp
     b26:	0106                	slli	sp,sp,0x1
     b28:	2005                	.insn	2, 0x2005
     b2a:	1209                	addi	tp,tp,-30 # ffffffffffffffe2 <__sheap+0xffffffffedffcfe2>
     b2c:	1600                	addi	s0,sp,800
     b2e:	2405                	addiw	s0,s0,1
     b30:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     b32:	0100                	addi	s0,sp,128
     b34:	2405                	addiw	s0,s0,1
     b36:	0009                	c.nop	2
     b38:	0300                	addi	s0,sp,384
     b3a:	0160                	addi	s0,sp,140
     b3c:	0e05                	addi	t3,t3,1
     b3e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     b40:	0000                	unimp
     b42:	0402                	c.slli64	s0
     b44:	3801                	addiw	a6,a6,-32
     b46:	1d05                	addi	s10,s10,-31
     b48:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     b4a:	0000                	unimp
     b4c:	0402                	c.slli64	s0
     b4e:	0600                	addi	s0,sp,768
     b50:	0518                	addi	a4,sp,640
     b52:	0915                	addi	s2,s2,5
     b54:	0002                	c.slli64	zero
     b56:	0106                	slli	sp,sp,0x1
     b58:	1505                	addi	a0,a0,-31
     b5a:	0009                	c.nop	2
     b5c:	0600                	addi	s0,sp,768
     b5e:	0915052f          	.insn	4, 0x0915052f
     b62:	0000                	unimp
     b64:	017eef03          	lwu	t5,23(t4)
     b68:	0105                	addi	sp,sp,1
     b6a:	0009                	c.nop	2
     b6c:	1800                	addi	s0,sp,48
     b6e:	0505                	addi	a0,a0,1
     b70:	0009                	c.nop	2
     b72:	0600                	addi	s0,sp,768
     b74:	0501                	addi	a0,a0,0
     b76:	00040913          	mv	s2,s0
     b7a:	0501                	addi	a0,a0,0
     b7c:	0908                	addi	a0,sp,144
     b7e:	0008                	.insn	2, 0x0008
     b80:	051a                	slli	a0,a0,0x6
     b82:	0912                	slli	s2,s2,0x4
     b84:	000c                	.insn	2, 0x000c
     b86:	0106                	slli	sp,sp,0x1
     b88:	0505                	addi	a0,a0,1
     b8a:	0009                	c.nop	2
     b8c:	0600                	addi	s0,sp,768
     b8e:	0501                	addi	a0,a0,0
     b90:	0916                	slli	s2,s2,0x5
     b92:	0006                	c.slli	zero,0x1
     b94:	0501                	addi	a0,a0,0
     b96:	0912                	slli	s2,s2,0x4
     b98:	0004                	.insn	2, 0x0004
     b9a:	0200                	addi	s0,sp,256
     b9c:	0104                	addi	s1,sp,128
     b9e:	05a4                	addi	s1,sp,712
     ba0:	091d                	addi	s2,s2,7
     ba2:	0002                	c.slli64	zero
     ba4:	0200                	addi	s0,sp,256
     ba6:	0004                	.insn	2, 0x0004
     ba8:	05014603          	lbu	a2,80(sp)
     bac:	090e                	slli	s2,s2,0x3
     bae:	0002                	c.slli64	zero
     bb0:	017fad03          	lw	s10,23(t6)
     bb4:	1605                	addi	a2,a2,-31
     bb6:	0409                	addi	s0,s0,2
     bb8:	0600                	addi	s0,sp,768
     bba:	0518                	addi	a4,sp,640
     bbc:	0905                	addi	s2,s2,1
     bbe:	0000                	unimp
     bc0:	051a                	slli	a0,a0,0x6
     bc2:	0905                	addi	s2,s2,1
     bc4:	0000                	unimp
     bc6:	0106                	slli	sp,sp,0x1
     bc8:	0505                	addi	a0,a0,1
     bca:	0009                	c.nop	2
     bcc:	0600                	addi	s0,sp,768
     bce:	05a1                	addi	a1,a1,8
     bd0:	0915                	addi	s2,s2,5
     bd2:	0002                	c.slli64	zero
     bd4:	0106                	slli	sp,sp,0x1
     bd6:	1505                	addi	a0,a0,-31
     bd8:	0009                	c.nop	2
     bda:	0600                	addi	s0,sp,768
     bdc:	017ee703          	lwu	a4,23(t4)
     be0:	0905                	addi	s2,s2,1
     be2:	0009                	c.nop	2
     be4:	0600                	addi	s0,sp,768
     be6:	0501                	addi	a0,a0,0
     be8:	0918                	addi	a4,sp,144
     bea:	000a                	c.slli	zero,0x2
     bec:	0501                	addi	a0,a0,0
     bee:	0918                	addi	a4,sp,144
     bf0:	0004                	.insn	2, 0x0004
     bf2:	1806                	slli	a6,a6,0x21
     bf4:	0905                	addi	s2,s2,1
     bf6:	0809                	addi	a6,a6,2
     bf8:	1800                	addi	s0,sp,48
     bfa:	0905                	addi	s2,s2,1
     bfc:	0009                	c.nop	2
     bfe:	0600                	addi	s0,sp,768
     c00:	090105bb          	.insn	4, 0x090105bb
     c04:	0006                	c.slli	zero,0x1
     c06:	017edc03          	lhu	s8,23(t4)
     c0a:	1305                	addi	t1,t1,-31
     c0c:	0809                	addi	a6,a6,2
     c0e:	0100                	addi	s0,sp,128
     c10:	1305                	addi	t1,t1,-31
     c12:	0009                	c.nop	2
     c14:	0600                	addi	s0,sp,768
     c16:	05ba                	slli	a1,a1,0xe
     c18:	0905                	addi	s2,s2,1
     c1a:	0000                	unimp
     c1c:	1806                	slli	a6,a6,0x21
     c1e:	0105                	addi	sp,sp,1
     c20:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     c22:	0100                	addi	s0,sp,128
     c24:	0105                	addi	sp,sp,1
     c26:	0609                	addi	a2,a2,2
     c28:	0600                	addi	s0,sp,768
     c2a:	05014603          	lbu	a2,80(sp)
     c2e:	0919                	addi	s2,s2,6
     c30:	0000                	unimp
     c32:	0518                	addi	a4,sp,640
     c34:	0919                	addi	s2,s2,6
     c36:	0000                	unimp
     c38:	0106                	slli	sp,sp,0x1
     c3a:	2405                	addiw	s0,s0,1
     c3c:	1209                	addi	tp,tp,-30 # ffffffffffffffe2 <__sheap+0xffffffffedffcfe2>
     c3e:	1600                	addi	s0,sp,800
     c40:	1d05                	addi	s10,s10,-31
     c42:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     c44:	0000                	unimp
     c46:	0402                	c.slli64	s0
     c48:	1801                	addi	a6,a6,-32
     c4a:	2105                	addiw	sp,sp,1
     c4c:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     c4e:	0100                	addi	s0,sp,128
     c50:	2105                	addiw	sp,sp,1
     c52:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     c54:	0100                	addi	s0,sp,128
     c56:	2105                	addiw	sp,sp,1
     c58:	0009                	c.nop	2
     c5a:	0000                	unimp
     c5c:	0402                	c.slli64	s0
     c5e:	0300                	addi	s0,sp,384
     c60:	016e                	slli	sp,sp,0x1b
     c62:	0b05                	addi	s6,s6,1
     c64:	0c09                	addi	s8,s8,2
     c66:	0600                	addi	s0,sp,768
     c68:	051f 0919 0000      	.insn	6, 0x0919051f
     c6e:	0518                	addi	a4,sp,640
     c70:	0919                	addi	s2,s2,6
     c72:	0000                	unimp
     c74:	0106                	slli	sp,sp,0x1
     c76:	2405                	addiw	s0,s0,1
     c78:	1209                	addi	tp,tp,-30 # ffffffffffffffe2 <__sheap+0xffffffffedffcfe2>
     c7a:	1600                	addi	s0,sp,800
     c7c:	1d05                	addi	s10,s10,-31
     c7e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     c80:	0000                	unimp
     c82:	0402                	c.slli64	s0
     c84:	1801                	addi	a6,a6,-32
     c86:	2105                	addiw	sp,sp,1
     c88:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     c8a:	0100                	addi	s0,sp,128
     c8c:	2105                	addiw	sp,sp,1
     c8e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     c90:	0000                	unimp
     c92:	0402                	c.slli64	s0
     c94:	0600                	addi	s0,sp,768
     c96:	0519                	addi	a0,a0,6
     c98:	0919                	addi	s2,s2,6
     c9a:	0000                	unimp
     c9c:	0518                	addi	a4,sp,640
     c9e:	0919                	addi	s2,s2,6
     ca0:	0000                	unimp
     ca2:	0106                	slli	sp,sp,0x1
     ca4:	2405                	addiw	s0,s0,1
     ca6:	1209                	addi	tp,tp,-30 # ffffffffffffffe2 <__sheap+0xffffffffedffcfe2>
     ca8:	1600                	addi	s0,sp,800
     caa:	1d05                	addi	s10,s10,-31
     cac:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     cae:	0000                	unimp
     cb0:	0402                	c.slli64	s0
     cb2:	1801                	addi	a6,a6,-32
     cb4:	2105                	addiw	sp,sp,1
     cb6:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     cb8:	0100                	addi	s0,sp,128
     cba:	2105                	addiw	sp,sp,1
     cbc:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     cbe:	0000                	unimp
     cc0:	0402                	c.slli64	s0
     cc2:	0600                	addi	s0,sp,768
     cc4:	0519                	addi	a0,a0,6
     cc6:	0919                	addi	s2,s2,6
     cc8:	0000                	unimp
     cca:	0518                	addi	a4,sp,640
     ccc:	0919                	addi	s2,s2,6
     cce:	0000                	unimp
     cd0:	0106                	slli	sp,sp,0x1
     cd2:	2405                	addiw	s0,s0,1
     cd4:	1209                	addi	tp,tp,-30 # ffffffffffffffe2 <__sheap+0xffffffffedffcfe2>
     cd6:	1600                	addi	s0,sp,800
     cd8:	1d05                	addi	s10,s10,-31
     cda:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     cdc:	0000                	unimp
     cde:	0402                	c.slli64	s0
     ce0:	1801                	addi	a6,a6,-32
     ce2:	2105                	addiw	sp,sp,1
     ce4:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     ce6:	0100                	addi	s0,sp,128
     ce8:	2105                	addiw	sp,sp,1
     cea:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     cec:	0000                	unimp
     cee:	0402                	c.slli64	s0
     cf0:	0600                	addi	s0,sp,768
     cf2:	017f9f03          	lh	t5,23(t6)
     cf6:	0905                	addi	s2,s2,1
     cf8:	0009                	c.nop	2
     cfa:	0300                	addi	s0,sp,384
     cfc:	0174                	addi	a3,sp,140
     cfe:	0105                	addi	sp,sp,1
     d00:	0009                	c.nop	2
     d02:	1800                	addi	s0,sp,48
     d04:	0505                	addi	a0,a0,1
     d06:	0009                	c.nop	2
     d08:	1800                	addi	s0,sp,48
     d0a:	0505                	addi	a0,a0,1
     d0c:	0009                	c.nop	2
     d0e:	1800                	addi	s0,sp,48
     d10:	0905                	addi	s2,s2,1
     d12:	0009                	c.nop	2
     d14:	0600                	addi	s0,sp,768
     d16:	0501                	addi	a0,a0,0
     d18:	0918                	addi	a4,sp,144
     d1a:	000a                	c.slli	zero,0x2
     d1c:	0518                	addi	a4,sp,640
     d1e:	0909                	addi	s2,s2,2
     d20:	0002                	c.slli64	zero
     d22:	0516                	slli	a0,a0,0x5
     d24:	0918                	addi	a4,sp,144
     d26:	0004                	.insn	2, 0x0004
     d28:	1806                	slli	a6,a6,0x21
     d2a:	0905                	addi	s2,s2,1
     d2c:	0809                	addi	a6,a6,2
     d2e:	1800                	addi	s0,sp,48
     d30:	0905                	addi	s2,s2,1
     d32:	0009                	c.nop	2
     d34:	0600                	addi	s0,sp,768
     d36:	0516                	slli	a0,a0,0x5
     d38:	0909                	addi	s2,s2,2
     d3a:	0006                	c.slli	zero,0x1
     d3c:	0501                	addi	a0,a0,0
     d3e:	0909                	addi	s2,s2,2
     d40:	0000                	unimp
     d42:	2f06                	fld	ft10,64(sp)
     d44:	0b05                	addi	s6,s6,1
     d46:	0009                	c.nop	2
     d48:	0600                	addi	s0,sp,768
     d4a:	0501                	addi	a0,a0,0
     d4c:	090e                	slli	s2,s2,0x3
     d4e:	0004                	.insn	2, 0x0004
     d50:	0516                	slli	a0,a0,0x5
     d52:	0002090b          	.insn	4, 0x0002090b
     d56:	0518                	addi	a4,sp,640
     d58:	0209000b          	.insn	4, 0x0209000b
     d5c:	0592                	slli	a1,a1,0x4
     d5e:	1200                	addi	s0,sp,288
     d60:	0000                	unimp
     d62:	0000                	unimp
     d64:	a706                	fsd	ft1,392(sp)
     d66:	1e05                	addi	t3,t3,-31
     d68:	0009                	c.nop	2
     d6a:	1800                	addi	s0,sp,48
     d6c:	0505                	addi	a0,a0,1
     d6e:	0009                	c.nop	2
     d70:	1800                	addi	s0,sp,48
     d72:	0505                	addi	a0,a0,1
     d74:	0009                	c.nop	2
     d76:	0600                	addi	s0,sp,768
     d78:	0515                	addi	a0,a0,5
     d7a:	091e                	slli	s2,s2,0x7
     d7c:	0002                	c.slli64	zero
     d7e:	0519                	addi	a0,a0,6
     d80:	0905                	addi	s2,s2,1
     d82:	0004                	.insn	2, 0x0004
     d84:	0515                	addi	a0,a0,5
     d86:	091e                	slli	s2,s2,0x7
     d88:	0002                	c.slli64	zero
     d8a:	051a                	slli	a0,a0,0x6
     d8c:	0911                	addi	s2,s2,4
     d8e:	0002                	c.slli64	zero
     d90:	0514                	addi	a3,sp,640
     d92:	091e                	slli	s2,s2,0x7
     d94:	0002                	c.slli64	zero
     d96:	0501                	addi	a0,a0,0
     d98:	091e                	slli	s2,s2,0x7
     d9a:	000c                	.insn	2, 0x000c
     d9c:	0519                	addi	a0,a0,6
     d9e:	0905                	addi	s2,s2,1
     da0:	0002                	c.slli64	zero
     da2:	1806                	slli	a6,a6,0x21
     da4:	0505                	addi	a0,a0,1
     da6:	0009                	c.nop	2
     da8:	0600                	addi	s0,sp,768
     daa:	0501                	addi	a0,a0,0
     dac:	0911                	addi	s2,s2,4
     dae:	0008                	.insn	2, 0x0008
     db0:	1806                	slli	a6,a6,0x21
     db2:	0505                	addi	a0,a0,1
     db4:	0009                	c.nop	2
     db6:	1800                	addi	s0,sp,48
     db8:	0505                	addi	a0,a0,1
     dba:	0009                	c.nop	2
     dbc:	0600                	addi	s0,sp,768
     dbe:	0518                	addi	a4,sp,640
     dc0:	0001                	nop
     dc2:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     dc4:	05ba                	slli	a1,a1,0xe
     dc6:	1200                	addi	s0,sp,288
     dc8:	0000                	unimp
     dca:	0000                	unimp
     dcc:	0100                	addi	s0,sp,128
     dce:	1501                	addi	a0,a0,-32
     dd0:	0001                	nop
     dd2:	0500                	addi	s0,sp,640
     dd4:	0800                	addi	s0,sp,16
     dd6:	4600                	lw	s0,8(a2)
     dd8:	0000                	unimp
     dda:	0100                	addi	s0,sp,128
     ddc:	0101                	addi	sp,sp,0
     dde:	f2f6                	sd	t4,352(sp)
     de0:	000d                	c.nop	3
     de2:	0101                	addi	sp,sp,0
     de4:	0101                	addi	sp,sp,0
     de6:	0000                	unimp
     de8:	0100                	addi	s0,sp,128
     dea:	0000                	unimp
     dec:	0101                	addi	sp,sp,0
     dee:	1f01                	addi	t5,t5,-32
     df0:	00015e03          	lhu	t3,0(sp)
     df4:	7c00                	ld	s0,56(s0)
     df6:	0000                	unimp
     df8:	0000                	unimp
     dfa:	0000                	unimp
     dfc:	0200                	addi	s0,sp,256
     dfe:	1f01                	addi	t5,t5,-32
     e00:	0b02                	c.slli64	s6
     e02:	a606                	fsd	ft1,264(sp)
     e04:	0000                	unimp
     e06:	0000                	unimp
     e08:	00a6                	slli	ra,ra,0x9
     e0a:	0000                	unimp
     e0c:	8c00                	.insn	2, 0x8c00
     e0e:	0001                	nop
     e10:	0200                	addi	s0,sp,256
     e12:	00000187          	.insn	4, 0x0187
     e16:	3302                	fld	ft6,32(sp)
     e18:	0000                	unimp
     e1a:	0100                	addi	s0,sp,128
     e1c:	0196                	slli	gp,gp,0x5
     e1e:	0000                	unimp
     e20:	0001                	nop
     e22:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     e24:	05ba                	slli	a1,a1,0xe
     e26:	1200                	addi	s0,sp,288
     e28:	0000                	unimp
     e2a:	0000                	unimp
     e2c:	051d                	addi	a0,a0,7
     e2e:	0919                	addi	s2,s2,6
     e30:	0000                	unimp
     e32:	0518                	addi	a4,sp,640
     e34:	0905                	addi	s2,s2,1
     e36:	0000                	unimp
     e38:	1606                	slli	a2,a2,0x21
     e3a:	1905                	addi	s2,s2,-31
     e3c:	0609                	addi	a2,a2,2
     e3e:	0100                	addi	s0,sp,128
     e40:	1905                	addi	s2,s2,-31
     e42:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     e44:	1800                	addi	s0,sp,48
     e46:	1105                	addi	sp,sp,-31
     e48:	0809                	addi	a6,a6,2
     e4a:	0100                	addi	s0,sp,128
     e4c:	1105                	addi	sp,sp,-31
     e4e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     e50:	0600                	addi	s0,sp,768
     e52:	0518                	addi	a4,sp,640
     e54:	0905                	addi	s2,s2,1
     e56:	0000                	unimp
     e58:	0204                	addi	s1,sp,256
     e5a:	052e                	slli	a0,a0,0xb
     e5c:	0901                	addi	s2,s2,0
     e5e:	0000                	unimp
     e60:	0518                	addi	a4,sp,640
     e62:	0905                	addi	s2,s2,1
     e64:	0000                	unimp
     e66:	0304                	addi	s1,sp,384
     e68:	05016403          	lwu	s0,80(sp)
     e6c:	0901                	addi	s2,s2,0
     e6e:	0000                	unimp
     e70:	051f 0905 0000      	.insn	6, 0x0905051f
     e76:	1906                	slli	s2,s2,0x21
     e78:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     e7a:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     e7c:	1500                	addi	s0,sp,672
     e7e:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     e80:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     e82:	0600                	addi	s0,sp,768
     e84:	0518                	addi	a4,sp,640
     e86:	0905                	addi	s2,s2,1
     e88:	0000                	unimp
     e8a:	0518                	addi	a4,sp,640
     e8c:	0905                	addi	s2,s2,1
     e8e:	0000                	unimp
     e90:	0518                	addi	a4,sp,640
     e92:	0905                	addi	s2,s2,1
     e94:	0000                	unimp
     e96:	0106                	slli	sp,sp,0x1
     e98:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     e9a:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     e9c:	0600                	addi	s0,sp,768
     e9e:	0518                	addi	a4,sp,640
     ea0:	0905                	addi	s2,s2,1
     ea2:	0000                	unimp
     ea4:	0106                	slli	sp,sp,0x1
     ea6:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     ea8:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     eaa:	0600                	addi	s0,sp,768
     eac:	0518                	addi	a4,sp,640
     eae:	0905                	addi	s2,s2,1
     eb0:	0000                	unimp
     eb2:	0106                	slli	sp,sp,0x1
     eb4:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
     eb6:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     eb8:	0600                	addi	s0,sp,768
     eba:	0518                	addi	a4,sp,640
     ebc:	0905                	addi	s2,s2,1
     ebe:	0004                	.insn	2, 0x0004
     ec0:	051d                	addi	a0,a0,7
     ec2:	0905                	addi	s2,s2,1
     ec4:	0000                	unimp
     ec6:	0106                	slli	sp,sp,0x1
     ec8:	0505                	addi	a0,a0,1
     eca:	0009                	c.nop	2
     ecc:	0400                	addi	s0,sp,512
     ece:	0301                	addi	t1,t1,0
     ed0:	0171                	addi	sp,sp,28
     ed2:	0105                	addi	sp,sp,1
     ed4:	0409                	addi	s0,s0,2
     ed6:	0100                	addi	s0,sp,128
     ed8:	0105                	addi	sp,sp,1
     eda:	0900                	addi	s0,sp,144
     edc:	e202                	sd	zero,256(sp)
     ede:	0005                	c.nop	1
     ee0:	0012                	c.slli	zero,0x4
     ee2:	0000                	unimp
     ee4:	0000                	unimp
     ee6:	0101                	addi	sp,sp,0
     ee8:	00df 0000 0005      	.insn	6, 0x0005000000df
     eee:	0008                	.insn	2, 0x0008
     ef0:	004a                	c.slli	zero,0x12
     ef2:	0000                	unimp
     ef4:	0101                	addi	sp,sp,0
     ef6:	f601                	bnez	a2,dfe <main-0x11fff202>
     ef8:	0df2                	slli	s11,s11,0x1c
     efa:	0100                	addi	s0,sp,128
     efc:	0101                	addi	sp,sp,0
     efe:	0001                	nop
     f00:	0000                	unimp
     f02:	0001                	nop
     f04:	0100                	addi	s0,sp,128
     f06:	0101                	addi	sp,sp,0
     f08:	041f 015e 0000      	.insn	6, 0x015e041f
     f0e:	007c                	addi	a5,sp,12
     f10:	0000                	unimp
     f12:	0000                	unimp
     f14:	0000                	unimp
     f16:	00b8                	addi	a4,sp,72
     f18:	0000                	unimp
     f1a:	0102                	c.slli64	sp
     f1c:	021f 060b 019f      	.insn	6, 0x019f060b021f
     f22:	0000                	unimp
     f24:	9f00                	.insn	2, 0x9f00
     f26:	0001                	nop
     f28:	0000                	unimp
     f2a:	000000af          	.insn	4, 0x00af
     f2e:	00003303          	ld	t1,0(zero) # 0 <main-0x12000000>
     f32:	0100                	addi	s0,sp,128
     f34:	003d                	c.nop	15
     f36:	0000                	unimp
     f38:	2c01                	sext.w	s8,s8
     f3a:	0000                	unimp
     f3c:	0200                	addi	s0,sp,256
     f3e:	0900                	addi	s0,sp,144
     f40:	e202                	sd	zero,256(sp)
     f42:	0005                	c.nop	1
     f44:	0012                	c.slli	zero,0x4
     f46:	0000                	unimp
     f48:	1f00                	addi	s0,sp,944
     f4a:	1f05                	addi	t5,t5,-31
     f4c:	0009                	c.nop	2
     f4e:	1800                	addi	s0,sp,48
     f50:	0505                	addi	a0,a0,1
     f52:	0009                	c.nop	2
     f54:	1800                	addi	s0,sp,48
     f56:	0505                	addi	a0,a0,1
     f58:	0009                	c.nop	2
     f5a:	0600                	addi	s0,sp,768
     f5c:	0515                	addi	a0,a0,5
     f5e:	091f 0002 0519      	.insn	6, 0x05190002091f
     f64:	0905                	addi	s2,s2,1
     f66:	0004                	.insn	2, 0x0004
     f68:	0515                	addi	a0,a0,5
     f6a:	091f 0004 051a      	.insn	6, 0x051a0004091f
     f70:	0905                	addi	s2,s2,1
     f72:	0008                	.insn	2, 0x0008
     f74:	0514                	addi	a3,sp,640
     f76:	091f 0002 0501      	.insn	6, 0x05010002091f
     f7c:	091f 000e 0519      	.insn	6, 0x0519000e091f
     f82:	0905                	addi	s2,s2,1
     f84:	0002                	c.slli64	zero
     f86:	1806                	slli	a6,a6,0x21
     f88:	0505                	addi	a0,a0,1
     f8a:	0809                	addi	a6,a6,2
     f8c:	1800                	addi	s0,sp,48
     f8e:	0505                	addi	a0,a0,1
     f90:	0c09                	addi	s8,s8,2
     f92:	1800                	addi	s0,sp,48
     f94:	0505                	addi	a0,a0,1
     f96:	0009                	c.nop	2
     f98:	1800                	addi	s0,sp,48
     f9a:	0505                	addi	a0,a0,1
     f9c:	0900                	addi	s0,sp,144
     f9e:	2202                	fld	ft4,0(sp)
     fa0:	0006                	c.slli	zero,0x1
     fa2:	0012                	c.slli	zero,0x4
     fa4:	0000                	unimp
     fa6:	1b00                	addi	s0,sp,432
     fa8:	1605                	addi	a2,a2,-31
     faa:	0009                	c.nop	2
     fac:	1800                	addi	s0,sp,48
     fae:	0505                	addi	a0,a0,1
     fb0:	0009                	c.nop	2
     fb2:	0600                	addi	s0,sp,768
     fb4:	0516                	slli	a0,a0,0x5
     fb6:	0916                	slli	s2,s2,0x5
     fb8:	0004                	.insn	2, 0x0004
     fba:	0518                	addi	a4,sp,640
     fbc:	0005                	c.nop	1
     fbe:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
     fc0:	062e                	slli	a2,a2,0xb
     fc2:	1200                	addi	s0,sp,288
     fc4:	0000                	unimp
     fc6:	0000                	unimp
     fc8:	0100                	addi	s0,sp,128
     fca:	af01                	j	16da <main-0x11ffe926>
     fcc:	0002                	c.slli64	zero
     fce:	0500                	addi	s0,sp,640
     fd0:	0800                	addi	s0,sp,16
     fd2:	4100                	lw	s0,0(a0)
     fd4:	0000                	unimp
     fd6:	0100                	addi	s0,sp,128
     fd8:	0101                	addi	sp,sp,0
     fda:	f2f6                	sd	t4,352(sp)
     fdc:	000d                	c.nop	3
     fde:	0101                	addi	sp,sp,0
     fe0:	0101                	addi	sp,sp,0
     fe2:	0000                	unimp
     fe4:	0100                	addi	s0,sp,128
     fe6:	0000                	unimp
     fe8:	0101                	addi	sp,sp,0
     fea:	1f01                	addi	t5,t5,-32
     fec:	00015e03          	lhu	t3,0(sp)
     ff0:	7c00                	ld	s0,56(s0)
     ff2:	0000                	unimp
     ff4:	0000                	unimp
     ff6:	0000                	unimp
     ff8:	0200                	addi	s0,sp,256
     ffa:	1f01                	addi	t5,t5,-32
     ffc:	0b02                	c.slli64	s6
     ffe:	a705                	j	171e <main-0x11ffe8e2>
    1000:	0001                	nop
    1002:	0000                	unimp
    1004:	000001a7          	.insn	4, 0x01a7
    1008:	8c00                	.insn	2, 0x8c00
    100a:	0001                	nop
    100c:	0200                	addi	s0,sp,256
    100e:	00000187          	.insn	4, 0x0187
    1012:	3302                	fld	ft6,32(sp)
    1014:	0000                	unimp
    1016:	0100                	addi	s0,sp,128
    1018:	0900                	addi	s0,sp,144
    101a:	2e02                	fld	ft8,0(sp)
    101c:	0006                	c.slli	zero,0x1
    101e:	0012                	c.slli	zero,0x4
    1020:	0000                	unimp
    1022:	1c00                	addi	s0,sp,560
    1024:	1105                	addi	sp,sp,-31
    1026:	0009                	c.nop	2
    1028:	1800                	addi	s0,sp,48
    102a:	0505                	addi	a0,a0,1
    102c:	0009                	c.nop	2
    102e:	0400                	addi	s0,sp,512
    1030:	2402                	fld	fs0,0(sp)
    1032:	0105                	addi	sp,sp,1
    1034:	0009                	c.nop	2
    1036:	1800                	addi	s0,sp,48
    1038:	0505                	addi	a0,a0,1
    103a:	0009                	c.nop	2
    103c:	0400                	addi	s0,sp,512
    103e:	01700303          	lb	t1,23(zero) # 17 <main-0x11ffffe9>
    1042:	0105                	addi	sp,sp,1
    1044:	0009                	c.nop	2
    1046:	1f00                	addi	s0,sp,944
    1048:	0505                	addi	a0,a0,1
    104a:	0009                	c.nop	2
    104c:	0600                	addi	s0,sp,768
    104e:	0501                	addi	a0,a0,0
    1050:	0912                	slli	s2,s2,0x4
    1052:	0002                	c.slli64	zero
    1054:	1806                	slli	a6,a6,0x21
    1056:	0505                	addi	a0,a0,1
    1058:	0009                	c.nop	2
    105a:	0600                	addi	s0,sp,768
    105c:	0501                	addi	a0,a0,0
    105e:	0912                	slli	s2,s2,0x4
    1060:	0002                	c.slli64	zero
    1062:	1806                	slli	a6,a6,0x21
    1064:	0505                	addi	a0,a0,1
    1066:	0009                	c.nop	2
    1068:	0600                	addi	s0,sp,768
    106a:	0501                	addi	a0,a0,0
    106c:	0912                	slli	s2,s2,0x4
    106e:	0002                	c.slli64	zero
    1070:	1806                	slli	a6,a6,0x21
    1072:	0505                	addi	a0,a0,1
    1074:	0009                	c.nop	2
    1076:	0600                	addi	s0,sp,768
    1078:	0501                	addi	a0,a0,0
    107a:	0912                	slli	s2,s2,0x4
    107c:	0002                	c.slli64	zero
    107e:	1806                	slli	a6,a6,0x21
    1080:	0505                	addi	a0,a0,1
    1082:	0009                	c.nop	2
    1084:	0600                	addi	s0,sp,768
    1086:	0501                	addi	a0,a0,0
    1088:	0912                	slli	s2,s2,0x4
    108a:	0002                	c.slli64	zero
    108c:	1806                	slli	a6,a6,0x21
    108e:	0505                	addi	a0,a0,1
    1090:	0009                	c.nop	2
    1092:	0600                	addi	s0,sp,768
    1094:	0501                	addi	a0,a0,0
    1096:	0912                	slli	s2,s2,0x4
    1098:	0002                	c.slli64	zero
    109a:	1806                	slli	a6,a6,0x21
    109c:	0505                	addi	a0,a0,1
    109e:	0409                	addi	s0,s0,2
    10a0:	1d00                	addi	s0,sp,688
    10a2:	0505                	addi	a0,a0,1
    10a4:	0009                	c.nop	2
    10a6:	0600                	addi	s0,sp,768
    10a8:	0501                	addi	a0,a0,0
    10aa:	0905                	addi	s2,s2,1
    10ac:	0000                	unimp
    10ae:	0204                	addi	s1,sp,256
    10b0:	0306                	slli	t1,t1,0x1
    10b2:	0105016f          	jal	sp,510c2 <main-0x11faef3e>
    10b6:	0009                	c.nop	2
    10b8:	1800                	addi	s0,sp,48
    10ba:	0505                	addi	a0,a0,1
    10bc:	0009                	c.nop	2
    10be:	0400                	addi	s0,sp,512
    10c0:	01051303          	lh	t1,16(a0)
    10c4:	0009                	c.nop	2
    10c6:	1f00                	addi	s0,sp,944
    10c8:	0505                	addi	a0,a0,1
    10ca:	0009                	c.nop	2
    10cc:	1800                	addi	s0,sp,48
    10ce:	0505                	addi	a0,a0,1
    10d0:	0009                	c.nop	2
    10d2:	1800                	addi	s0,sp,48
    10d4:	0505                	addi	a0,a0,1
    10d6:	0009                	c.nop	2
    10d8:	1800                	addi	s0,sp,48
    10da:	0505                	addi	a0,a0,1
    10dc:	0009                	c.nop	2
    10de:	1800                	addi	s0,sp,48
    10e0:	0505                	addi	a0,a0,1
    10e2:	0009                	c.nop	2
    10e4:	1800                	addi	s0,sp,48
    10e6:	0505                	addi	a0,a0,1
    10e8:	0009                	c.nop	2
    10ea:	0600                	addi	s0,sp,768
    10ec:	0501                	addi	a0,a0,0
    10ee:	0912                	slli	s2,s2,0x4
    10f0:	0002                	c.slli64	zero
    10f2:	1806                	slli	a6,a6,0x21
    10f4:	0505                	addi	a0,a0,1
    10f6:	0409                	addi	s0,s0,2
    10f8:	1d00                	addi	s0,sp,688
    10fa:	0505                	addi	a0,a0,1
    10fc:	0009                	c.nop	2
    10fe:	0600                	addi	s0,sp,768
    1100:	0501                	addi	a0,a0,0
    1102:	0905                	addi	s2,s2,1
    1104:	0000                	unimp
    1106:	0104                	addi	s1,sp,128
    1108:	0306                	slli	t1,t1,0x1
    110a:	0505016f          	jal	sp,5115a <main-0x11faeea6>
    110e:	0900                	addi	s0,sp,144
    1110:	4402                	lw	s0,0(sp)
    1112:	0006                	c.slli	zero,0x1
    1114:	0012                	c.slli	zero,0x4
    1116:	0000                	unimp
    1118:	1b00                	addi	s0,sp,432
    111a:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    111c:	0009                	c.nop	2
    111e:	1800                	addi	s0,sp,48
    1120:	0505                	addi	a0,a0,1
    1122:	0009                	c.nop	2
    1124:	0400                	addi	s0,sp,512
    1126:	7602                	ld	a2,32(sp)
    1128:	0105                	addi	sp,sp,1
    112a:	0009                	c.nop	2
    112c:	1800                	addi	s0,sp,48
    112e:	0505                	addi	a0,a0,1
    1130:	0009                	c.nop	2
    1132:	0400                	addi	s0,sp,512
    1134:	7f980303          	lb	t1,2041(a6)
    1138:	0501                	addi	a0,a0,0
    113a:	0901                	addi	s2,s2,0
    113c:	0000                	unimp
    113e:	051f 0905 0000      	.insn	6, 0x0905051f
    1144:	0106                	slli	sp,sp,0x1
    1146:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1148:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    114a:	0600                	addi	s0,sp,768
    114c:	0518                	addi	a4,sp,640
    114e:	0905                	addi	s2,s2,1
    1150:	0000                	unimp
    1152:	0106                	slli	sp,sp,0x1
    1154:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1156:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1158:	0600                	addi	s0,sp,768
    115a:	0518                	addi	a4,sp,640
    115c:	0905                	addi	s2,s2,1
    115e:	0000                	unimp
    1160:	0106                	slli	sp,sp,0x1
    1162:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1164:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1166:	0600                	addi	s0,sp,768
    1168:	0518                	addi	a4,sp,640
    116a:	0905                	addi	s2,s2,1
    116c:	0000                	unimp
    116e:	0106                	slli	sp,sp,0x1
    1170:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1172:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1174:	0600                	addi	s0,sp,768
    1176:	0518                	addi	a4,sp,640
    1178:	0905                	addi	s2,s2,1
    117a:	0000                	unimp
    117c:	0106                	slli	sp,sp,0x1
    117e:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1180:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1182:	0600                	addi	s0,sp,768
    1184:	0518                	addi	a4,sp,640
    1186:	0905                	addi	s2,s2,1
    1188:	0000                	unimp
    118a:	0106                	slli	sp,sp,0x1
    118c:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    118e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1190:	0600                	addi	s0,sp,768
    1192:	0518                	addi	a4,sp,640
    1194:	0905                	addi	s2,s2,1
    1196:	0004                	.insn	2, 0x0004
    1198:	051d                	addi	a0,a0,7
    119a:	0905                	addi	s2,s2,1
    119c:	0000                	unimp
    119e:	0106                	slli	sp,sp,0x1
    11a0:	0505                	addi	a0,a0,1
    11a2:	0009                	c.nop	2
    11a4:	0400                	addi	s0,sp,512
    11a6:	0301                	addi	t1,t1,0
    11a8:	0175                	addi	sp,sp,29
    11aa:	0105                	addi	sp,sp,1
    11ac:	0900                	addi	s0,sp,144
    11ae:	5602                	lw	a2,32(sp)
    11b0:	0006                	c.slli	zero,0x1
    11b2:	0012                	c.slli	zero,0x4
    11b4:	0000                	unimp
    11b6:	0600                	addi	s0,sp,768
    11b8:	051a                	slli	a0,a0,0x6
    11ba:	00000913          	li	s2,0
    11be:	0518                	addi	a4,sp,640
    11c0:	0905                	addi	s2,s2,1
    11c2:	0000                	unimp
    11c4:	0518                	addi	a4,sp,640
    11c6:	0905                	addi	s2,s2,1
    11c8:	0000                	unimp
    11ca:	0106                	slli	sp,sp,0x1
    11cc:	1005                	c.nop	-31
    11ce:	0809                	addi	a6,a6,2
    11d0:	0100                	addi	s0,sp,128
    11d2:	0805                	addi	a6,a6,1
    11d4:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    11d6:	0600                	addi	s0,sp,768
    11d8:	0518                	addi	a4,sp,640
    11da:	0909                	addi	s2,s2,2
    11dc:	0000                	unimp
    11de:	0204                	addi	s1,sp,256
    11e0:	0501                	addi	a0,a0,0
    11e2:	0901                	addi	s2,s2,0
    11e4:	0000                	unimp
    11e6:	0518                	addi	a4,sp,640
    11e8:	0905                	addi	s2,s2,1
    11ea:	0000                	unimp
    11ec:	0304                	addi	s1,sp,384
    11ee:	05017003          	.insn	4, 0x05017003
    11f2:	0901                	addi	s2,s2,0
    11f4:	0000                	unimp
    11f6:	051f 0905 0000      	.insn	6, 0x0905051f
    11fc:	0518                	addi	a4,sp,640
    11fe:	0905                	addi	s2,s2,1
    1200:	0000                	unimp
    1202:	0106                	slli	sp,sp,0x1
    1204:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1206:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1208:	0600                	addi	s0,sp,768
    120a:	0518                	addi	a4,sp,640
    120c:	0905                	addi	s2,s2,1
    120e:	0000                	unimp
    1210:	0106                	slli	sp,sp,0x1
    1212:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1214:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1216:	0600                	addi	s0,sp,768
    1218:	0518                	addi	a4,sp,640
    121a:	0905                	addi	s2,s2,1
    121c:	0000                	unimp
    121e:	0106                	slli	sp,sp,0x1
    1220:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1222:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1224:	0600                	addi	s0,sp,768
    1226:	0518                	addi	a4,sp,640
    1228:	0905                	addi	s2,s2,1
    122a:	0000                	unimp
    122c:	0106                	slli	sp,sp,0x1
    122e:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1230:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1232:	0600                	addi	s0,sp,768
    1234:	0518                	addi	a4,sp,640
    1236:	0905                	addi	s2,s2,1
    1238:	0000                	unimp
    123a:	0106                	slli	sp,sp,0x1
    123c:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    123e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1240:	0600                	addi	s0,sp,768
    1242:	0518                	addi	a4,sp,640
    1244:	0905                	addi	s2,s2,1
    1246:	0004                	.insn	2, 0x0004
    1248:	051d                	addi	a0,a0,7
    124a:	0905                	addi	s2,s2,1
    124c:	0000                	unimp
    124e:	0106                	slli	sp,sp,0x1
    1250:	0505                	addi	a0,a0,1
    1252:	0009                	c.nop	2
    1254:	0400                	addi	s0,sp,512
    1256:	0001                	nop
    1258:	0402                	c.slli64	s0
    125a:	1201                	addi	tp,tp,-32 # ffffffffffffffe0 <__sheap+0xffffffffedffcfe0>
    125c:	1005                	c.nop	-31
    125e:	0809                	addi	a6,a6,2
    1260:	0000                	unimp
    1262:	0402                	c.slli64	s0
    1264:	0600                	addi	s0,sp,768
    1266:	0519                	addi	a0,a0,6
    1268:	0905                	addi	s2,s2,1
    126a:	0000                	unimp
    126c:	1806                	slli	a6,a6,0x21
    126e:	0105                	addi	sp,sp,1
    1270:	0900                	addi	s0,sp,144
    1272:	7802                	ld	a6,32(sp)
    1274:	0006                	c.slli	zero,0x1
    1276:	0012                	c.slli	zero,0x4
    1278:	0000                	unimp
    127a:	0000                	unimp
    127c:	0101                	addi	sp,sp,0
    127e:	0086                	slli	ra,ra,0x1
    1280:	0000                	unimp
    1282:	0005                	c.nop	1
    1284:	0008                	.insn	2, 0x0008
    1286:	003c                	addi	a5,sp,8
    1288:	0000                	unimp
    128a:	0101                	addi	sp,sp,0
    128c:	f601                	bnez	a2,1194 <main-0x11ffee6c>
    128e:	0df2                	slli	s11,s11,0x1c
    1290:	0100                	addi	s0,sp,128
    1292:	0101                	addi	sp,sp,0
    1294:	0001                	nop
    1296:	0000                	unimp
    1298:	0001                	nop
    129a:	0100                	addi	s0,sp,128
    129c:	0101                	addi	sp,sp,0
    129e:	031f 015e 0000      	.insn	6, 0x015e031f
    12a4:	007c                	addi	a5,sp,12
    12a6:	0000                	unimp
    12a8:	0000                	unimp
    12aa:	0000                	unimp
    12ac:	0102                	c.slli64	sp
    12ae:	021f 040b 01ae      	.insn	6, 0x01ae040b021f
    12b4:	0000                	unimp
    12b6:	ae00                	fsd	fs0,24(a2)
    12b8:	0001                	nop
    12ba:	0000                	unimp
    12bc:	00000033          	add	zero,zero,zero
    12c0:	2c01                	sext.w	s8,s8
    12c2:	0000                	unimp
    12c4:	0200                	addi	s0,sp,256
    12c6:	0900                	addi	s0,sp,144
    12c8:	7802                	ld	a6,32(sp)
    12ca:	0006                	c.slli	zero,0x1
    12cc:	0012                	c.slli	zero,0x4
    12ce:	0000                	unimp
    12d0:	2000                	fld	fs0,0(s0)
    12d2:	0c05                	addi	s8,s8,1
    12d4:	0009                	c.nop	2
    12d6:	1800                	addi	s0,sp,48
    12d8:	0505                	addi	a0,a0,1
    12da:	0009                	c.nop	2
    12dc:	0600                	addi	s0,sp,768
    12de:	0516                	slli	a0,a0,0x5
    12e0:	090c                	addi	a1,sp,144
    12e2:	0002                	c.slli64	zero
    12e4:	0518                	addi	a4,sp,640
    12e6:	0905                	addi	s2,s2,1
    12e8:	0004                	.insn	2, 0x0004
    12ea:	0516                	slli	a0,a0,0x5
    12ec:	090c                	addi	a1,sp,144
    12ee:	0002                	c.slli64	zero
    12f0:	0518                	addi	a4,sp,640
    12f2:	0905                	addi	s2,s2,1
    12f4:	0008                	.insn	2, 0x0008
    12f6:	1806                	slli	a6,a6,0x21
    12f8:	0505                	addi	a0,a0,1
    12fa:	0900                	addi	s0,sp,144
    12fc:	9002                	ebreak
    12fe:	0006                	c.slli	zero,0x1
    1300:	0012                	c.slli	zero,0x4
    1302:	0000                	unimp
    1304:	0000                	unimp
    1306:	0101                	addi	sp,sp,0
    1308:	0074                	addi	a3,sp,12
    130a:	0000                	unimp
    130c:	0005                	c.nop	1
    130e:	0008                	.insn	2, 0x0008
    1310:	002a                	c.slli	zero,0xa
    1312:	0000                	unimp
    1314:	0101                	addi	sp,sp,0
    1316:	fb01                	bnez	a4,1226 <main-0x11ffedda>
    1318:	0d0e                	slli	s10,s10,0x3
    131a:	0100                	addi	s0,sp,128
    131c:	0101                	addi	sp,sp,0
    131e:	0001                	nop
    1320:	0000                	unimp
    1322:	0001                	nop
    1324:	0100                	addi	s0,sp,128
    1326:	0101                	addi	sp,sp,0
    1328:	011f 015e 0000      	.insn	6, 0x015e011f
    132e:	0102                	c.slli64	sp
    1330:	021f 020f 01b5      	.insn	6, 0x01b5020f021f
    1336:	0000                	unimp
    1338:	b500                	fsd	fs0,40(a0)
    133a:	0001                	nop
    133c:	0000                	unimp
    133e:	0900                	addi	s0,sp,144
    1340:	9002                	ebreak
    1342:	0006                	c.slli	zero,0x1
    1344:	0012                	c.slli	zero,0x4
    1346:	0000                	unimp
    1348:	1500                	addi	s0,sp,672
    134a:	02090103          	lb	sp,32(s2)
    134e:	0100                	addi	s0,sp,128
    1350:	02090103          	lb	sp,32(s2)
    1354:	0100                	addi	s0,sp,128
    1356:	02090103          	lb	sp,32(s2)
    135a:	0100                	addi	s0,sp,128
    135c:	02090203          	lb	tp,32(s2)
    1360:	0100                	addi	s0,sp,128
    1362:	08090203          	lb	tp,128(s2)
    1366:	0100                	addi	s0,sp,128
    1368:	02090103          	lb	sp,32(s2)
    136c:	0100                	addi	s0,sp,128
    136e:	02090103          	lb	sp,32(s2)
    1372:	0100                	addi	s0,sp,128
    1374:	02090203          	lb	tp,32(s2)
    1378:	0100                	addi	s0,sp,128
    137a:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    137c:	0000                	unimp
    137e:	0101                	addi	sp,sp,0
    1380:	04b4                	addi	a3,sp,584
    1382:	0000                	unimp
    1384:	0005                	c.nop	1
    1386:	0008                	.insn	2, 0x0008
    1388:	00000033          	add	zero,zero,zero
    138c:	0101                	addi	sp,sp,0
    138e:	f601                	bnez	a2,1296 <main-0x11ffed6a>
    1390:	0df2                	slli	s11,s11,0x1c
    1392:	0100                	addi	s0,sp,128
    1394:	0101                	addi	sp,sp,0
    1396:	0001                	nop
    1398:	0000                	unimp
    139a:	0001                	nop
    139c:	0100                	addi	s0,sp,128
    139e:	0101                	addi	sp,sp,0
    13a0:	021f 013c 0000      	.insn	6, 0x013c021f
    13a6:	007c                	addi	a5,sp,12
    13a8:	0000                	unimp
    13aa:	0102                	c.slli64	sp
    13ac:	021f 030b 01bc      	.insn	6, 0x01bc030b021f
    13b2:	0000                	unimp
    13b4:	bc00                	fsd	fs0,56(s0)
    13b6:	0001                	nop
    13b8:	0000                	unimp
    13ba:	00000033          	add	zero,zero,zero
    13be:	0001                	nop
    13c0:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    13c2:	06a8                	addi	a0,sp,840
    13c4:	1200                	addi	s0,sp,288
    13c6:	0000                	unimp
    13c8:	0000                	unimp
    13ca:	0520                	addi	s0,sp,648
    13cc:	0920                	addi	s0,sp,152
    13ce:	0000                	unimp
    13d0:	0518                	addi	a4,sp,640
    13d2:	0905                	addi	s2,s2,1
    13d4:	0000                	unimp
    13d6:	0518                	addi	a4,sp,640
    13d8:	0905                	addi	s2,s2,1
    13da:	0000                	unimp
    13dc:	0501                	addi	a0,a0,0
    13de:	090c                	addi	a1,sp,144
    13e0:	0000                	unimp
    13e2:	0106                	slli	sp,sp,0x1
    13e4:	0c05                	addi	s8,s8,1
    13e6:	0409                	addi	s0,s0,2
    13e8:	1600                	addi	s0,sp,800
    13ea:	0905                	addi	s2,s2,1
    13ec:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    13ee:	0600                	addi	s0,sp,768
    13f0:	0519                	addi	a0,a0,6
    13f2:	0909                	addi	s2,s2,2
    13f4:	0000                	unimp
    13f6:	0106                	slli	sp,sp,0x1
    13f8:	0b05                	addi	s6,s6,1
    13fa:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    13fc:	0100                	addi	s0,sp,128
    13fe:	0e05                	addi	t3,t3,1
    1400:	0409                	addi	s0,s0,2
    1402:	0600                	addi	s0,sp,768
    1404:	0516                	slli	a0,a0,0x5
    1406:	090c                	addi	a1,sp,144
    1408:	0000                	unimp
    140a:	0106                	slli	sp,sp,0x1
    140c:	0c05                	addi	s8,s8,1
    140e:	0409                	addi	s0,s0,2
    1410:	0600                	addi	s0,sp,768
    1412:	051a                	slli	a0,a0,0x6
    1414:	0905                	addi	s2,s2,1
    1416:	0000                	unimp
    1418:	1806                	slli	a6,a6,0x21
    141a:	0105                	addi	sp,sp,1
    141c:	0900                	addi	s0,sp,144
    141e:	ba02                	fsd	ft0,304(sp)
    1420:	0006                	c.slli	zero,0x1
    1422:	0012                	c.slli	zero,0x4
    1424:	0000                	unimp
    1426:	0600                	addi	s0,sp,768
    1428:	051a                	slli	a0,a0,0x6
    142a:	092e                	slli	s2,s2,0xb
    142c:	0000                	unimp
    142e:	0518                	addi	a4,sp,640
    1430:	0905                	addi	s2,s2,1
    1432:	0000                	unimp
    1434:	0518                	addi	a4,sp,640
    1436:	0905                	addi	s2,s2,1
    1438:	0000                	unimp
    143a:	0518                	addi	a4,sp,640
    143c:	0905                	addi	s2,s2,1
    143e:	0000                	unimp
    1440:	0501                	addi	a0,a0,0
    1442:	090c                	addi	a1,sp,144
    1444:	0000                	unimp
    1446:	0106                	slli	sp,sp,0x1
    1448:	0c05                	addi	s8,s8,1
    144a:	0409                	addi	s0,s0,2
    144c:	1500                	addi	s0,sp,672
    144e:	0905                	addi	s2,s2,1
    1450:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1452:	0600                	addi	s0,sp,768
    1454:	051a                	slli	a0,a0,0x6
    1456:	0909                	addi	s2,s2,2
    1458:	0000                	unimp
    145a:	0106                	slli	sp,sp,0x1
    145c:	1005                	c.nop	-31
    145e:	0409                	addi	s0,s0,2
    1460:	0100                	addi	s0,sp,128
    1462:	0b05                	addi	s6,s6,1
    1464:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1466:	0100                	addi	s0,sp,128
    1468:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    146a:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    146c:	0100                	addi	s0,sp,128
    146e:	0e05                	addi	t3,t3,1
    1470:	0409                	addi	s0,s0,2
    1472:	0600                	addi	s0,sp,768
    1474:	0516                	slli	a0,a0,0x5
    1476:	090c                	addi	a1,sp,144
    1478:	0000                	unimp
    147a:	0106                	slli	sp,sp,0x1
    147c:	0c05                	addi	s8,s8,1
    147e:	0409                	addi	s0,s0,2
    1480:	0600                	addi	s0,sp,768
    1482:	051a                	slli	a0,a0,0x6
    1484:	0905                	addi	s2,s2,1
    1486:	0000                	unimp
    1488:	1806                	slli	a6,a6,0x21
    148a:	0105                	addi	sp,sp,1
    148c:	0900                	addi	s0,sp,144
    148e:	d202                	sw	zero,36(sp)
    1490:	0006                	c.slli	zero,0x1
    1492:	0012                	c.slli	zero,0x4
    1494:	0000                	unimp
    1496:	0600                	addi	s0,sp,768
    1498:	051a                	slli	a0,a0,0x6
    149a:	0931                	addi	s2,s2,12
    149c:	0000                	unimp
    149e:	0518                	addi	a4,sp,640
    14a0:	0905                	addi	s2,s2,1
    14a2:	0000                	unimp
    14a4:	0518                	addi	a4,sp,640
    14a6:	0905                	addi	s2,s2,1
    14a8:	0000                	unimp
    14aa:	0518                	addi	a4,sp,640
    14ac:	0905                	addi	s2,s2,1
    14ae:	0000                	unimp
    14b0:	0501                	addi	a0,a0,0
    14b2:	090a                	slli	s2,s2,0x2
    14b4:	0000                	unimp
    14b6:	0200                	addi	s0,sp,256
    14b8:	0104                	addi	s1,sp,128
    14ba:	0501                	addi	a0,a0,0
    14bc:	0919                	addi	s2,s2,6
    14be:	0004                	.insn	2, 0x0004
    14c0:	0106                	slli	sp,sp,0x1
    14c2:	1905                	addi	s2,s2,-31
    14c4:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    14c6:	0100                	addi	s0,sp,128
    14c8:	1905                	addi	s2,s2,-31
    14ca:	0409                	addi	s0,s0,2
    14cc:	0000                	unimp
    14ce:	0402                	c.slli64	s0
    14d0:	0600                	addi	s0,sp,768
    14d2:	0518                	addi	a4,sp,640
    14d4:	0909                	addi	s2,s2,2
    14d6:	0000                	unimp
    14d8:	0200                	addi	s0,sp,256
    14da:	0204                	addi	s1,sp,256
    14dc:	0516                	slli	a0,a0,0x5
    14de:	091f 0000 0200      	.insn	6, 0x02000000091f
    14e4:	0104                	addi	s1,sp,128
    14e6:	0501                	addi	a0,a0,0
    14e8:	0919                	addi	s2,s2,6
    14ea:	0000                	unimp
    14ec:	0200                	addi	s0,sp,256
    14ee:	0004                	.insn	2, 0x0004
    14f0:	1806                	slli	a6,a6,0x21
    14f2:	0f05                	addi	t5,t5,1
    14f4:	0409                	addi	s0,s0,2
    14f6:	0100                	addi	s0,sp,128
    14f8:	1805                	addi	a6,a6,-31
    14fa:	0409                	addi	s0,s0,2
    14fc:	0000                	unimp
    14fe:	0402                	c.slli64	s0
    1500:	1601                	addi	a2,a2,-32
    1502:	1905                	addi	s2,s2,-31
    1504:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1506:	0100                	addi	s0,sp,128
    1508:	1905                	addi	s2,s2,-31
    150a:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    150c:	0000                	unimp
    150e:	0402                	c.slli64	s0
    1510:	1800                	addi	s0,sp,48
    1512:	0c05                	addi	s8,s8,1
    1514:	0409                	addi	s0,s0,2
    1516:	0600                	addi	s0,sp,768
    1518:	0518                	addi	a4,sp,640
    151a:	090d                	addi	s2,s2,3
    151c:	0000                	unimp
    151e:	0106                	slli	sp,sp,0x1
    1520:	2205                	addiw	tp,tp,1 # 1 <main-0x11ffffff>
    1522:	0409                	addi	s0,s0,2
    1524:	0100                	addi	s0,sp,128
    1526:	1405                	addi	s0,s0,-31
    1528:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    152a:	0100                	addi	s0,sp,128
    152c:	1405                	addi	s0,s0,-31
    152e:	0009                	c.nop	2
    1530:	1a00                	addi	s0,sp,304
    1532:	0c05                	addi	s8,s8,1
    1534:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1536:	1800                	addi	s0,sp,48
    1538:	0105                	addi	sp,sp,1
    153a:	0900                	addi	s0,sp,144
    153c:	f602                	sd	zero,296(sp)
    153e:	0006                	c.slli	zero,0x1
    1540:	0012                	c.slli	zero,0x4
    1542:	0000                	unimp
    1544:	0600                	addi	s0,sp,768
    1546:	051a                	slli	a0,a0,0x6
    1548:	00000917          	auipc	s2,0x0
    154c:	0518                	addi	a4,sp,640
    154e:	0905                	addi	s2,s2,1 # 1549 <main-0x11ffeab7>
    1550:	0000                	unimp
    1552:	0518                	addi	a4,sp,640
    1554:	0905                	addi	s2,s2,1
    1556:	0000                	unimp
    1558:	0501                	addi	a0,a0,0
    155a:	090c                	addi	a1,sp,144
    155c:	0006                	c.slli	zero,0x1
    155e:	1606                	slli	a2,a2,0x21
    1560:	1105                	addi	sp,sp,-31
    1562:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1564:	0600                	addi	s0,sp,768
    1566:	0519                	addi	a0,a0,6
    1568:	0909                	addi	s2,s2,2
    156a:	0000                	unimp
    156c:	1606                	slli	a2,a2,0x21
    156e:	0c05                	addi	s8,s8,1
    1570:	0409                	addi	s0,s0,2
    1572:	1800                	addi	s0,sp,48
    1574:	0a05                	addi	s4,s4,1
    1576:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1578:	0600                	addi	s0,sp,768
    157a:	0516                	slli	a0,a0,0x5
    157c:	090c                	addi	a1,sp,144
    157e:	0002                	c.slli64	zero
    1580:	1a06                	slli	s4,s4,0x21
    1582:	1605                	addi	a2,a2,-31
    1584:	0409                	addi	s0,s0,2
    1586:	0100                	addi	s0,sp,128
    1588:	1605                	addi	a2,a2,-31
    158a:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    158c:	1400                	addi	s0,sp,544
    158e:	0c05                	addi	s8,s8,1
    1590:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1592:	0600                	addi	s0,sp,768
    1594:	051a                	slli	a0,a0,0x6
    1596:	0905                	addi	s2,s2,1
    1598:	0000                	unimp
    159a:	1806                	slli	a6,a6,0x21
    159c:	0105                	addi	sp,sp,1
    159e:	0900                	addi	s0,sp,144
    15a0:	1002                	c.slli	zero,0x20
    15a2:	00120007          	.insn	4, 0x00120007
    15a6:	0000                	unimp
    15a8:	0600                	addi	s0,sp,768
    15aa:	051a                	slli	a0,a0,0x6
    15ac:	0925                	addi	s2,s2,9
    15ae:	0000                	unimp
    15b0:	0518                	addi	a4,sp,640
    15b2:	0905                	addi	s2,s2,1
    15b4:	0000                	unimp
    15b6:	0518                	addi	a4,sp,640
    15b8:	0905                	addi	s2,s2,1
    15ba:	0000                	unimp
    15bc:	1606                	slli	a2,a2,0x21
    15be:	0b05                	addi	s6,s6,1
    15c0:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    15c2:	0000                	unimp
    15c4:	0402                	c.slli64	s0
    15c6:	0601                	addi	a2,a2,0
    15c8:	0518                	addi	a4,sp,640
    15ca:	090c                	addi	a1,sp,144
    15cc:	0000                	unimp
    15ce:	0106                	slli	sp,sp,0x1
    15d0:	1405                	addi	s0,s0,-31
    15d2:	0409                	addi	s0,s0,2
    15d4:	0100                	addi	s0,sp,128
    15d6:	1805                	addi	a6,a6,-31
    15d8:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    15da:	0100                	addi	s0,sp,128
    15dc:	0f05                	addi	t5,t5,1
    15de:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    15e0:	0100                	addi	s0,sp,128
    15e2:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    15e4:	0409                	addi	s0,s0,2
    15e6:	0100                	addi	s0,sp,128
    15e8:	0c05                	addi	s8,s8,1
    15ea:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    15ec:	0000                	unimp
    15ee:	0402                	c.slli64	s0
    15f0:	0600                	addi	s0,sp,768
    15f2:	0518                	addi	a4,sp,640
    15f4:	0905                	addi	s2,s2,1
    15f6:	0000                	unimp
    15f8:	1806                	slli	a6,a6,0x21
    15fa:	0105                	addi	sp,sp,1
    15fc:	0900                	addi	s0,sp,144
    15fe:	2202                	fld	ft4,0(sp)
    1600:	00120007          	.insn	4, 0x00120007
    1604:	0000                	unimp
    1606:	0600                	addi	s0,sp,768
    1608:	051a                	slli	a0,a0,0x6
    160a:	0000092f          	.insn	4, 0x092f
    160e:	0518                	addi	a4,sp,640
    1610:	0905                	addi	s2,s2,1
    1612:	0000                	unimp
    1614:	0518                	addi	a4,sp,640
    1616:	0905                	addi	s2,s2,1
    1618:	0000                	unimp
    161a:	0518                	addi	a4,sp,640
    161c:	0905                	addi	s2,s2,1
    161e:	0000                	unimp
    1620:	0200                	addi	s0,sp,256
    1622:	0104                	addi	s1,sp,128
    1624:	0501                	addi	a0,a0,0
    1626:	00000917          	auipc	s2,0x0
    162a:	0200                	addi	s0,sp,256
    162c:	0004                	.insn	2, 0x0004
    162e:	0106                	slli	sp,sp,0x1
    1630:	0c05                	addi	s8,s8,1
    1632:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1634:	0000                	unimp
    1636:	0402                	c.slli64	s0
    1638:	0101                	addi	sp,sp,0
    163a:	1705                	addi	a4,a4,-31
    163c:	0409                	addi	s0,s0,2
    163e:	0000                	unimp
    1640:	0402                	c.slli64	s0
    1642:	1800                	addi	s0,sp,48
    1644:	0e05                	addi	t3,t3,1
    1646:	0409                	addi	s0,s0,2
    1648:	0000                	unimp
    164a:	0402                	c.slli64	s0
    164c:	0604                	addi	s1,sp,768
    164e:	0516                	slli	a0,a0,0x5
    1650:	0002092b          	.insn	4, 0x0002092b
    1654:	0200                	addi	s0,sp,256
    1656:	0104                	addi	s1,sp,128
    1658:	0501                	addi	a0,a0,0
    165a:	00040917          	auipc	s2,0x40
    165e:	0200                	addi	s0,sp,256
    1660:	0004                	.insn	2, 0x0004
    1662:	0518                	addi	a4,sp,640
    1664:	0909                	addi	s2,s2,2 # 4165c <main-0x11fbe9a4>
    1666:	0000                	unimp
    1668:	0200                	addi	s0,sp,256
    166a:	0304                	addi	s1,sp,384
    166c:	1606                	slli	a2,a2,0x21
    166e:	1d05                	addi	s10,s10,-31
    1670:	0809                	addi	a6,a6,2
    1672:	0000                	unimp
    1674:	0402                	c.slli64	s0
    1676:	1800                	addi	s0,sp,48
    1678:	0e05                	addi	t3,t3,1
    167a:	0409                	addi	s0,s0,2
    167c:	0000                	unimp
    167e:	0402                	c.slli64	s0
    1680:	17051603          	lh	a2,368(a0)
    1684:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1686:	0000                	unimp
    1688:	0402                	c.slli64	s0
    168a:	0601                	addi	a2,a2,0
    168c:	051a                	slli	a0,a0,0x6
    168e:	090e                	slli	s2,s2,0x3
    1690:	0004                	.insn	2, 0x0004
    1692:	0106                	slli	sp,sp,0x1
    1694:	0e05                	addi	t3,t3,1
    1696:	0409                	addi	s0,s0,2
    1698:	0000                	unimp
    169a:	0402                	c.slli64	s0
    169c:	0600                	addi	s0,sp,768
    169e:	0518                	addi	a4,sp,640
    16a0:	0909                	addi	s2,s2,2
    16a2:	0000                	unimp
    16a4:	0106                	slli	sp,sp,0x1
    16a6:	0e05                	addi	t3,t3,1
    16a8:	0409                	addi	s0,s0,2
    16aa:	0000                	unimp
    16ac:	0402                	c.slli64	s0
    16ae:	0602                	c.slli64	a2
    16b0:	0516                	slli	a0,a0,0x5
    16b2:	0914                	addi	a3,sp,144
    16b4:	0000                	unimp
    16b6:	0200                	addi	s0,sp,256
    16b8:	0104                	addi	s1,sp,128
    16ba:	0501                	addi	a0,a0,0
    16bc:	090e                	slli	s2,s2,0x3
    16be:	0002                	c.slli64	zero
    16c0:	0106                	slli	sp,sp,0x1
    16c2:	0e05                	addi	t3,t3,1
    16c4:	0409                	addi	s0,s0,2
    16c6:	0000                	unimp
    16c8:	0402                	c.slli64	s0
    16ca:	1b00                	addi	s0,sp,432
    16cc:	0105                	addi	sp,sp,1
    16ce:	0900                	addi	s0,sp,144
    16d0:	5402                	lw	s0,32(sp)
    16d2:	00120007          	.insn	4, 0x00120007
    16d6:	0000                	unimp
    16d8:	0600                	addi	s0,sp,768
    16da:	051a                	slli	a0,a0,0x6
    16dc:	0925                	addi	s2,s2,9
    16de:	0000                	unimp
    16e0:	0518                	addi	a4,sp,640
    16e2:	0905                	addi	s2,s2,1
    16e4:	0000                	unimp
    16e6:	0518                	addi	a4,sp,640
    16e8:	0905                	addi	s2,s2,1
    16ea:	0000                	unimp
    16ec:	0501                	addi	a0,a0,0
    16ee:	090c                	addi	a1,sp,144
    16f0:	0006                	c.slli	zero,0x1
    16f2:	1606                	slli	a2,a2,0x21
    16f4:	0b05                	addi	s6,s6,1
    16f6:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    16f8:	0600                	addi	s0,sp,768
    16fa:	0519                	addi	a0,a0,6
    16fc:	0909                	addi	s2,s2,2
    16fe:	0000                	unimp
    1700:	1606                	slli	a2,a2,0x21
    1702:	0c05                	addi	s8,s8,1
    1704:	0409                	addi	s0,s0,2
    1706:	1800                	addi	s0,sp,48
    1708:	0a05                	addi	s4,s4,1
    170a:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    170c:	0600                	addi	s0,sp,768
    170e:	0516                	slli	a0,a0,0x5
    1710:	090c                	addi	a1,sp,144
    1712:	0002                	c.slli64	zero
    1714:	0200                	addi	s0,sp,256
    1716:	0104                	addi	s1,sp,128
    1718:	051a                	slli	a0,a0,0x6
    171a:	090c                	addi	a1,sp,144
    171c:	0000                	unimp
    171e:	0106                	slli	sp,sp,0x1
    1720:	1405                	addi	s0,s0,-31
    1722:	0409                	addi	s0,s0,2
    1724:	0100                	addi	s0,sp,128
    1726:	1805                	addi	a6,a6,-31
    1728:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    172a:	0100                	addi	s0,sp,128
    172c:	0f05                	addi	t5,t5,1
    172e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1730:	0100                	addi	s0,sp,128
    1732:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1734:	0409                	addi	s0,s0,2
    1736:	0100                	addi	s0,sp,128
    1738:	0c05                	addi	s8,s8,1
    173a:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    173c:	0000                	unimp
    173e:	0402                	c.slli64	s0
    1740:	0600                	addi	s0,sp,768
    1742:	0518                	addi	a4,sp,640
    1744:	0905                	addi	s2,s2,1
    1746:	0000                	unimp
    1748:	1806                	slli	a6,a6,0x21
    174a:	0105                	addi	sp,sp,1
    174c:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    174e:	0000                	unimp
    1750:	0402                	c.slli64	s0
    1752:	1501                	addi	a0,a0,-32
    1754:	1405                	addi	s0,s0,-31
    1756:	0409                	addi	s0,s0,2
    1758:	0000                	unimp
    175a:	0402                	c.slli64	s0
    175c:	1300                	addi	s0,sp,416
    175e:	0b05                	addi	s6,s6,1
    1760:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1762:	0000                	unimp
    1764:	0402                	c.slli64	s0
    1766:	0601                	addi	a2,a2,0
    1768:	090c051b          	addiw	a0,s8,144
    176c:	0000                	unimp
    176e:	0106                	slli	sp,sp,0x1
    1770:	1805                	addi	a6,a6,-31
    1772:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1774:	0100                	addi	s0,sp,128
    1776:	1205                	addi	tp,tp,-31 # ffffffffffffffe1 <__sheap+0xffffffffedffcfe1>
    1778:	0409                	addi	s0,s0,2
    177a:	0100                	addi	s0,sp,128
    177c:	0f05                	addi	t5,t5,1
    177e:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    1780:	0100                	addi	s0,sp,128
    1782:	0c05                	addi	s8,s8,1
    1784:	0900                	addi	s0,sp,144
    1786:	8602                	jr	a2
    1788:	00120007          	.insn	4, 0x00120007
    178c:	0000                	unimp
    178e:	0000                	unimp
    1790:	0402                	c.slli64	s0
    1792:	0600                	addi	s0,sp,768
    1794:	051c                	addi	a5,sp,640
    1796:	0928                	addi	a0,sp,152
    1798:	0000                	unimp
    179a:	0518                	addi	a4,sp,640
    179c:	0905                	addi	s2,s2,1
    179e:	0000                	unimp
    17a0:	0106                	slli	sp,sp,0x1
    17a2:	0c05                	addi	s8,s8,1
    17a4:	0409                	addi	s0,s0,2
    17a6:	0600                	addi	s0,sp,768
    17a8:	0501                	addi	a0,a0,0
    17aa:	0910                	addi	a2,sp,144
    17ac:	0004                	.insn	2, 0x0004
    17ae:	0106                	slli	sp,sp,0x1
    17b0:	0c05                	addi	s8,s8,1
    17b2:	0409                	addi	s0,s0,2
    17b4:	0100                	addi	s0,sp,128
    17b6:	1005                	c.nop	-31
    17b8:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    17ba:	0100                	addi	s0,sp,128
    17bc:	1005                	c.nop	-31
    17be:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    17c0:	0600                	addi	s0,sp,768
    17c2:	0518                	addi	a4,sp,640
    17c4:	0909                	addi	s2,s2,2
    17c6:	0000                	unimp
    17c8:	0200                	addi	s0,sp,256
    17ca:	0104                	addi	s1,sp,128
    17cc:	1606                	slli	a2,a2,0x21
    17ce:	1b05                	addi	s6,s6,-31
    17d0:	0409                	addi	s0,s0,2
    17d2:	0000                	unimp
    17d4:	0402                	c.slli64	s0
    17d6:	1800                	addi	s0,sp,48
    17d8:	0b05                	addi	s6,s6,1
    17da:	0209                	addi	tp,tp,2 # 2 <main-0x11fffffe>
    17dc:	0600                	addi	s0,sp,768
    17de:	0518                	addi	a4,sp,640
    17e0:	0909                	addi	s2,s2,2
    17e2:	0000                	unimp
    17e4:	0515                	addi	a0,a0,5
    17e6:	0910                	addi	a2,sp,144
    17e8:	0000                	unimp
    17ea:	0200                	addi	s0,sp,256
    17ec:	0104                	addi	s1,sp,128
    17ee:	0106                	slli	sp,sp,0x1
    17f0:	1005                	c.nop	-31
    17f2:	0409                	addi	s0,s0,2
    17f4:	0000                	unimp
    17f6:	0402                	c.slli64	s0
    17f8:	1b00                	addi	s0,sp,432
    17fa:	1405                	addi	s0,s0,-31
    17fc:	0409                	addi	s0,s0,2
    17fe:	0600                	addi	s0,sp,768
    1800:	0501                	addi	a0,a0,0
    1802:	0905                	addi	s2,s2,1
    1804:	0000                	unimp
    1806:	1806                	slli	a6,a6,0x21
    1808:	0105                	addi	sp,sp,1
    180a:	0409                	addi	s0,s0,2
    180c:	1600                	addi	s0,sp,800
    180e:	1f05                	addi	t5,t5,-31
    1810:	0609                	addi	a2,a2,2
    1812:	0600                	addi	s0,sp,768
    1814:	0501                	addi	a0,a0,0
    1816:	0905                	addi	s2,s2,1
    1818:	0000                	unimp
    181a:	1806                	slli	a6,a6,0x21
    181c:	0105                	addi	sp,sp,1
    181e:	0409                	addi	s0,s0,2
    1820:	1600                	addi	s0,sp,800
    1822:	1f05                	addi	t5,t5,-31
    1824:	0609                	addi	a2,a2,2
    1826:	0100                	addi	s0,sp,128
    1828:	1f05                	addi	t5,t5,-31
    182a:	0900                	addi	s0,sp,144
    182c:	ba02                	fsd	ft0,304(sp)
    182e:	00120007          	.insn	4, 0x00120007
    1832:	0000                	unimp
    1834:	0000                	unimp
    1836:	0101                	addi	sp,sp,0

Disassembly of section .debug_str:

0000000000000000 <.debug_str>:
   0:	6f6c                	ld	a1,216(a4)
   2:	676e                	ld	a4,216(sp)
   4:	6c20                	ld	s0,88(s0)
   6:	20676e6f          	jal	t3,7620c <main-0x11f89df4>
   a:	6e69                	lui	t3,0x1a
   c:	0074                	addi	a3,sp,12
   e:	7369                	lui	t1,0xffffa
  10:	7a69                	lui	s4,0xffffa
  12:	0065                	c.nop	25
  14:	6f6c                	ld	a1,216(a4)
  16:	676e                	ld	a4,216(sp)
  18:	6c20                	ld	s0,88(s0)
  1a:	20676e6f          	jal	t3,76220 <main-0x11f89de0>
  1e:	6e75                	lui	t3,0x1d
  20:	6e676973          	csrrsi	s2,0x6e6,14
  24:	6465                	lui	s0,0x19
  26:	6920                	ld	s0,80(a0)
  28:	746e                	ld	s0,248(sp)
  2a:	4700                	lw	s0,8(a4)
  2c:	554e                	lw	a0,240(sp)
  2e:	4320                	lw	s0,64(a4)
  30:	3131                	addiw	sp,sp,-20
  32:	3120                	fld	fs0,96(a0)
  34:	2e35                	addiw	t3,t3,13 # 1d00d <main-0x11fe2ff3>
  36:	2e31                	addiw	t3,t3,12
  38:	2030                	fld	fa2,64(s0)
  3a:	6d2d                	lui	s10,0xb
  3c:	6f6e                	ld	t5,216(sp)
  3e:	722d                	lui	tp,0xfffeb
  40:	6c65                	lui	s8,0x19
  42:	7861                	lui	a6,0xffff8
  44:	2d20                	fld	fs0,88(a0)
  46:	616d                	addi	sp,sp,240
  48:	6962                	ld	s2,24(sp)
  4a:	6c3d                	lui	s8,0xf
  4c:	3670                	fld	fa2,232(a2)
  4e:	6434                	ld	a3,72(s0)
  50:	2d20                	fld	fs0,88(a0)
  52:	636d                	lui	t1,0x1b
  54:	6f6d                	lui	t5,0x1b
  56:	6564                	ld	s1,200(a0)
  58:	3d6c                	fld	fa1,248(a0)
  5a:	656d                	lui	a0,0x1b
  5c:	6164                	ld	s1,192(a0)
  5e:	796e                	ld	s2,248(sp)
  60:	2d20                	fld	fs0,88(a0)
  62:	746d                	lui	s0,0xffffb
  64:	6e75                	lui	t3,0x1d
  66:	3d65                	addiw	s10,s10,-7 # aff9 <main-0x11ff5007>
  68:	6f72                	ld	t5,280(sp)
  6a:	74656b63          	bltu	a0,t1,7c0 <main-0x11fff840>
  6e:	2d20                	fld	fs0,88(a0)
  70:	696d                	lui	s2,0x1b
  72:	732d6173          	csrrsi	sp,mhpmevent18h,26
  76:	6570                	ld	a2,200(a0)
  78:	30323d63          	.insn	4, 0x30323d63
  7c:	3931                	addiw	s2,s2,-20 # 1afec <main-0x11fe5014>
  7e:	3231                	addiw	tp,tp,-20 # fffffffffffeafec <__sheap+0xffffffffedfe7fec>
  80:	3331                	addiw	t1,t1,-20 # 1afec <main-0x11fe5014>
  82:	2d20                	fld	fs0,88(a0)
  84:	616d                	addi	sp,sp,240
  86:	6372                	ld	t1,280(sp)
  88:	3d68                	fld	fa0,248(a0)
  8a:	7672                	ld	a2,312(sp)
  8c:	3436                	fld	fs0,360(sp)
  8e:	6d69                	lui	s10,0x1a
  90:	6661                	lui	a2,0x18
  92:	6364                	ld	s1,192(a4)
  94:	7a5f 6369 7273      	.insn	6, 0x727363697a5f
  9a:	7a5f 6669 6e65      	.insn	6, 0x6e6566697a5f
  a0:	5f696563          	bltu	s2,s6,68a <main-0x11fff976>
  a4:	6d7a                	ld	s10,408(sp)
  a6:	756d                	lui	a0,0xffffb
  a8:	5f6c                	lw	a1,124(a4)
  aa:	617a                	ld	sp,408(sp)
  ac:	6d61                	lui	s10,0x18
  ae:	617a5f6f          	jal	t5,a5ec4 <main-0x11f5a13c>
  b2:	726c                	ld	a1,224(a2)
  b4:	7a5f6373          	csrrsi	t1,tcontrol,30
  b8:	7a5f6163          	bltu	t5,t0,85a <main-0x11fff7a6>
  bc:	2d206463          	bltu	zero,s2,384 <main-0x11fffc7c>
  c0:	4f2d2067          	.insn	4, 0x4f2d2067
  c4:	2032                	fld	ft0,264(sp)
  c6:	732d                	lui	t1,0xfffeb
  c8:	6474                	ld	a3,200(s0)
  ca:	673d                	lui	a4,0xf
  cc:	756e                	ld	a0,248(sp)
  ce:	3131                	addiw	sp,sp,-20
  d0:	2d20                	fld	fs0,88(a0)
  d2:	6e66                	ld	t3,88(sp)
  d4:	75622d6f          	jal	s10,2282a <main-0x11fdd7d6>
  d8:	6c69                	lui	s8,0x1a
  da:	6974                	ld	a3,208(a0)
  dc:	206e                	fld	ft0,216(sp)
  de:	662d                	lui	a2,0xb
  e0:	7266                	ld	tp,120(sp)
  e2:	6565                	lui	a0,0x19
  e4:	6e617473          	csrrci	s0,0x6e6,2
  e8:	6964                	ld	s1,208(a0)
  ea:	676e                	ld	a4,216(sp)
  ec:	2d20                	fld	fs0,88(a0)
  ee:	6e66                	ld	t3,88(sp)
  f0:	74732d6f          	jal	s10,33036 <main-0x11fccfca>
  f4:	6361                	lui	t1,0x18
  f6:	72702d6b          	.insn	4, 0x72702d6b
  fa:	6365746f          	jal	s0,57730 <main-0x11fa88d0>
  fe:	6f74                	ld	a3,216(a4)
 100:	2072                	fld	ft0,280(sp)
 102:	662d                	lui	a2,0xb
 104:	6f6e                	ld	t5,216(sp)
 106:	702d                	c.lui	zero,0xfffeb
 108:	6569                	lui	a0,0x1a
 10a:	7500                	ld	s0,40(a0)
 10c:	736e                	ld	t1,248(sp)
 10e:	6769                	lui	a4,0x1a
 110:	656e                	ld	a0,216(sp)
 112:	2064                	fld	fs1,192(s0)
 114:	72616863          	bltu	sp,t1,844 <main-0x11fff7bc>
 118:	6400                	ld	s0,8(s0)
 11a:	6c62756f          	jal	a0,277e0 <main-0x11fd8820>
 11e:	0065                	c.nop	25
 120:	7261                	lui	tp,0xffff8
 122:	63006367          	.insn	4, 0x63006367
 126:	746e756f          	jal	a0,e786c <main-0x11f18794>
 12a:	7265                	lui	tp,0xffff9
 12c:	7300                	ld	s0,32(a4)
 12e:	6f68                	ld	a0,216(a4)
 130:	7472                	ld	s0,312(sp)
 132:	7520                	ld	s0,104(a0)
 134:	736e                	ld	t1,248(sp)
 136:	6769                	lui	a4,0x1a
 138:	656e                	ld	a0,216(sp)
 13a:	2064                	fld	fs1,192(s0)
 13c:	6e69                	lui	t3,0x1a
 13e:	0074                	addi	a3,sp,12
 140:	7261                	lui	tp,0xffff8
 142:	66007667          	.insn	4, 0x66007667
 146:	6f6c                	ld	a1,216(a4)
 148:	7461                	lui	s0,0xffff8
 14a:	7300                	ld	s0,32(a4)
 14c:	6f68                	ld	a0,216(a4)
 14e:	7472                	ld	s0,312(sp)
 150:	6920                	ld	s0,80(a0)
 152:	746e                	ld	s0,248(sp)
 154:	6400                	ld	s0,8(s0)
 156:	6769                	lui	a4,0x1a
 158:	7469                	lui	s0,0xffffa
 15a:	5f5f0073          	.insn	4, 0x5f5f0073
 15e:	7562                	ld	a0,56(sp)
 160:	6c69                	lui	s8,0x1a
 162:	6974                	ld	a3,208(a0)
 164:	5f6e                	lw	t5,248(sp)
 166:	6176                	ld	sp,344(sp)
 168:	6c5f 7369 0074      	.insn	6, 0x007473696c5f
 16e:	7270                	ld	a2,224(a2)
 170:	6e69                	lui	t3,0x1a
 172:	6574                	ld	a3,200(a0)
 174:	5f64                	lw	s1,124(a4)
 176:	656c                	ld	a1,200(a0)
 178:	006e                	c.slli	zero,0x1b
 17a:	7369                	lui	t1,0xffffa
 17c:	735f 6769 656e      	.insn	6, 0x656e6769735f
 182:	0064                	addi	s1,sp,12
 184:	7570                	ld	a2,232(a0)
 186:	6374                	ld	a3,192(a4)
 188:	5f00                	lw	s0,56(a4)
 18a:	6f42                	ld	t5,16(sp)
 18c:	76006c6f          	jal	s8,68ec <main-0x11ff9714>
 190:	7270                	ld	a2,224(a2)
 192:	6e69                	lui	t3,0x1a
 194:	6674                	ld	a3,200(a2)
 196:	7000                	ld	s0,32(s0)
 198:	6972                	ld	s2,280(sp)
 19a:	746e                	ld	s0,248(sp)
 19c:	6465                	lui	s0,0x19
 19e:	5f00                	lw	s0,56(a4)
 1a0:	675f 756e 5f63      	.insn	6, 0x5f63756e675f
 1a6:	6176                	ld	sp,344(sp)
 1a8:	6c5f 7369 0074      	.insn	6, 0x007473696c5f
 1ae:	6f74                	ld	a3,216(a4)
 1b0:	6174                	ld	a3,192(a0)
 1b2:	5f6c                	lw	a1,124(a4)
 1b4:	656c                	ld	a1,200(a0)
 1b6:	006e                	c.slli	zero,0x1b
 1b8:	7562                	ld	a0,56(sp)
 1ba:	5f66                	lw	t5,120(sp)
 1bc:	6e69                	lui	t3,0x1a
 1be:	6564                	ld	s1,200(a0)
 1c0:	0078                	addi	a4,sp,12
 1c2:	7270                	ld	a2,224(a2)
 1c4:	6e69                	lui	t3,0x1a
 1c6:	5f74                	lw	a3,124(a4)
 1c8:	6e69                	lui	t3,0x1a
 1ca:	0074                	addi	a3,sp,12
 1cc:	6c66                	ld	s8,88(sp)
 1ce:	7375                	lui	t1,0xffffd
 1d0:	0068                	addi	a0,sp,12
 1d2:	6261                	lui	tp,0x18
 1d4:	756e5f73          	csrrwi	t5,0x756,28
 1d8:	006d                	c.nop	27
 1da:	5f5f 7570 7374      	.insn	6, 0x737475705f5f
 1e0:	5f00                	lw	s0,56(a4)
 1e2:	705f 6e61 6369      	.insn	6, 0x63696e61705f
 1e8:	7500                	ld	s0,40(a0)
 1ea:	657a6973          	csrrsi	s2,hviprio2h,20
 1ee:	7300                	ld	s0,32(a4)
 1f0:	6769                	lui	a4,0x1a
 1f2:	006e                	c.slli	zero,0x1b
 1f4:	7270                	ld	a2,224(a2)
 1f6:	6e69                	lui	t3,0x1a
 1f8:	5f74                	lw	a3,124(a4)
 1fa:	00727473          	csrrci	s0,0x7,4
 1fe:	6162                	ld	sp,24(sp)
 200:	61006573          	csrrsi	a0,0x610,0
 204:	6772                	ld	a4,280(sp)
 206:	0030                	addi	a2,sp,8
 208:	7261                	lui	tp,0xffff8
 20a:	73003367          	.insn	4, 0x73003367
 20e:	7379                	lui	t1,0xffffe
 210:	6f6e                	ld	t5,216(sp)
 212:	6100                	ld	s0,0(a0)
 214:	6772                	ld	a4,280(sp)
 216:	0031                	c.nop	12
 218:	7261                	lui	tp,0xffff8
 21a:	61003267          	.insn	4, 0x61003267
 21e:	6772                	ld	a4,280(sp)
 220:	0034                	addi	a3,sp,8
 222:	7261                	lui	tp,0xffff8
 224:	735f6863          	bltu	t5,s5,954 <main-0x11fff6ac>
 228:	7379                	lui	t1,0xffffe
 22a:	6c6c6163          	bltu	s8,t1,8ec <main-0x11fff714>
 22e:	7300                	ld	s0,32(a4)
 230:	7379                	lui	t1,0xffffe
 232:	645f 6762 705f      	.insn	6, 0x705f6762645f
 238:	7475                	lui	s0,0xffffd
 23a:	74730073          	.insn	4, 0x74730073
 23e:	6c72                	ld	s8,280(sp)
 240:	6e65                	lui	t3,0x19
 242:	7400                	ld	s0,40(s0)
 244:	7361                	lui	t1,0xffff8
 246:	78655f6b          	.insn	4, 0x78655f6b
 24a:	7469                	lui	s0,0xffffa
 24c:	5f00                	lw	s0,56(a4)
 24e:	705f 6e61 6369      	.insn	6, 0x63696e61705f
 254:	6e5f 5f6f 736d      	.insn	6, 0x736d5f6f6e5f
 25a:	69740067          	jr	1687(s0) # ffffffffffffa697 <__sheap+0xffffffffedff7697>
 25e:	5f64                	lw	s1,124(a4)
 260:	0074                	addi	a3,sp,12
 262:	5f737973          	csrrci	s2,0x5f7,6
 266:	6174                	ld	a3,192(a0)
 268:	795f6b73          	csrrsi	s6,0x795,30
 26c:	6569                	lui	a0,0x1a
 26e:	646c                	ld	a1,200(s0)
 270:	6300                	ld	s0,0(a4)
 272:	6361                	lui	t1,0x18
 274:	6568                	ld	a0,200(a0)
 276:	0064                	addi	s1,sp,12
 278:	5f737973          	csrrci	s2,0x5f7,6
 27c:	6174                	ld	a3,192(a0)
 27e:	675f6b73          	csrrsi	s6,0x675,30
 282:	7465                	lui	s0,0xffff9
 284:	6974                	ld	a3,208(a0)
 286:	0064                	addi	s1,sp,12
 288:	5f737973          	csrrci	s2,0x5f7,6
 28c:	6174                	ld	a3,192(a0)
 28e:	6b5f6b73          	csrrsi	s6,0x6b5,30
 292:	6c69                	lui	s8,0x1a
 294:	006c                	addi	a1,sp,12
 296:	5f5f 616d 6e69      	.insn	6, 0x6e69616d5f5f
 29c:	6300                	ld	s0,0(a4)
 29e:	7472                	ld	s0,312(sp)
 2a0:	0030                	addi	a2,sp,8
 2a2:	616d                	addi	sp,sp,240
 2a4:	6e69                	lui	t3,0x1a
 2a6:	532e                	lw	t1,232(sp)
 2a8:	2f00                	fld	fs0,24(a4)
 2aa:	6f68                	ld	a0,216(a4)
 2ac:	656d                	lui	a0,0x1b
 2ae:	726f642f          	.insn	4, 0x726f642f
 2b2:	6375                	lui	t1,0x1d
 2b4:	6568                	ld	a0,200(a0)
 2b6:	6f72702f          	.insn	4, 0x6f72702f
 2ba:	656a                	ld	a0,152(sp)
 2bc:	2f737463          	bgeu	t1,s7,5a4 <main-0x11fffa5c>
 2c0:	6f636f63          	bltu	t1,s6,9be <main-0x11fff642>
 2c4:	73752f73          	csrrs	t5,mhpmevent23h,a0
 2c8:	6170                	ld	a2,192(a0)
 2ca:	6c2f6563          	bltu	t5,sp,994 <main-0x11fff66c>
 2ce:	6269                	lui	tp,0x1a
 2d0:	4e470063          	beq	a4,tp,7b0 <main-0x11fff850>
 2d4:	2055                	.insn	2, 0x2055
 2d6:	5341                	li	t1,-16
 2d8:	3220                	fld	fs0,96(a2)
 2da:	342e                	fld	fs0,232(sp)
 2dc:	0034                	addi	a3,sp,8
 2de:	656d                	lui	a0,0x1b
 2e0:	636d                	lui	t1,0x1b
 2e2:	706d                	c.lui	zero,0xffffb
 2e4:	7300                	ld	s0,32(a4)
 2e6:	7274                	ld	a3,224(a2)
 2e8:	00797063          	bgeu	s2,t2,2e8 <main-0x11fffd18>
 2ec:	63727473          	csrrci	s0,0x637,4
 2f0:	7461                	lui	s0,0xffff8
 2f2:	7300                	ld	s0,32(a4)
 2f4:	7274                	ld	a3,224(a2)
 2f6:	636e                	ld	t1,216(sp)
 2f8:	7970                	ld	a2,240(a0)
 2fa:	6d00                	ld	s0,24(a0)
 2fc:	6d65                	lui	s10,0x19
 2fe:	00746573          	csrrsi	a0,0x7,8
 302:	6564                	ld	s1,200(a0)
 304:	73007473          	csrrci	s0,mhpmevent16h,0
 308:	7274                	ld	a3,224(a2)
 30a:	00706d63          	bltu	zero,t2,324 <main-0x11fffcdc>
 30e:	656d                	lui	a0,0x1b
 310:	636d                	lui	t1,0x1b
 312:	7970                	ld	a2,240(a0)
	...

Disassembly of section .debug_line_str:

0000000000000000 <.debug_line_str>:
   0:	6d6f682f          	.insn	4, 0x6d6f682f
   4:	2f65                	addiw	t5,t5,25 # 1b019 <main-0x11fe4fe7>
   6:	6f64                	ld	s1,216(a4)
   8:	7572                	ld	a0,312(sp)
   a:	2f656863          	bltu	a0,s6,2fa <main-0x11fffd06>
   e:	7270                	ld	a2,224(a2)
  10:	63656a6f          	jal	s4,56646 <main-0x11fa99ba>
  14:	7374                	ld	a3,224(a4)
  16:	636f632f          	.insn	4, 0x636f632f
  1a:	692f736f          	jal	t1,f76ac <main-0x11f08954>
  1e:	636e                	ld	t1,216(sp)
  20:	756c                	ld	a1,232(a0)
  22:	6564                	ld	s1,200(a0)
  24:	7073752f          	.insn	4, 0x7073752f
  28:	6361                	lui	t1,0x18
  2a:	0065                	c.nop	25
  2c:	6174                	ld	a3,192(a0)
  2e:	682e6b73          	csrrsi	s6,0x682,28
  32:	7000                	ld	s0,32(s0)
  34:	6572                	ld	a0,280(sp)
  36:	756c                	ld	a1,232(a0)
  38:	6564                	ld	s1,200(a0)
  3a:	682e                	ld	a6,200(sp)
  3c:	7000                	ld	s0,32(s0)
  3e:	6972                	ld	s2,280(sp)
  40:	746e                	ld	s0,248(sp)
  42:	2e66                	fld	ft8,88(sp)
  44:	0068                	addi	a0,sp,12
  46:	616d                	addi	sp,sp,240
  48:	6e69                	lui	t3,0x1a
  4a:	632e                	ld	t1,200(sp)
  4c:	2f00                	fld	fs0,24(a4)
  4e:	6f68                	ld	a0,216(a4)
  50:	656d                	lui	a0,0x1b
  52:	726f642f          	.insn	4, 0x726f642f
  56:	6375                	lui	t1,0x1d
  58:	6568                	ld	a0,200(a0)
  5a:	6f72702f          	.insn	4, 0x6f72702f
  5e:	656a                	ld	a0,152(sp)
  60:	2f737463          	bgeu	t1,s7,348 <main-0x11fffcb8>
  64:	6f636f63          	bltu	t1,s6,762 <main-0x11fff89e>
  68:	73752f73          	csrrs	t5,mhpmevent23h,a0
  6c:	6170                	ld	a2,192(a0)
  6e:	612f6563          	bltu	t5,s2,678 <main-0x11fff988>
  72:	7070                	ld	a2,224(s0)
  74:	65682f73          	csrrs	t5,hviprio1h,a6
  78:	6c6c                	ld	a1,216(s0)
  7a:	682f006f          	j	f06fc <main-0x11f0f904>
  7e:	2f656d6f          	jal	s10,56374 <main-0x11fa9c8c>
  82:	6f64                	ld	s1,216(a4)
  84:	7572                	ld	a0,312(sp)
  86:	2f656863          	bltu	a0,s6,376 <main-0x11fffc8a>
  8a:	7270                	ld	a2,224(a2)
  8c:	63656a6f          	jal	s4,566c2 <main-0x11fa993e>
  90:	7374                	ld	a3,224(a4)
  92:	636f632f          	.insn	4, 0x636f632f
  96:	692f736f          	jal	t1,f7728 <main-0x11f088d8>
  9a:	636e                	ld	t1,216(sp)
  9c:	756c                	ld	a1,232(a0)
  9e:	6564                	ld	s1,200(a0)
  a0:	62696c2f          	.insn	4, 0x62696c2f
  a4:	72700073          	.insn	4, 0x72700073
  a8:	6e69                	lui	t3,0x1a
  aa:	6674                	ld	a3,200(a2)
  ac:	632e                	ld	t1,200(sp)
  ae:	7300                	ld	s0,32(a4)
  b0:	6474                	ld	a3,200(s0)
  b2:	7261                	lui	tp,0xffff8
  b4:	00682e67          	.insn	4, 0x00682e67
  b8:	6d6f682f          	.insn	4, 0x6d6f682f
  bc:	2f65                	addiw	t5,t5,25
  be:	6f64                	ld	s1,216(a4)
  c0:	7572                	ld	a0,312(sp)
  c2:	2f656863          	bltu	a0,s6,3b2 <main-0x11fffc4e>
  c6:	6f74                	ld	a3,216(a4)
  c8:	68636c6f          	jal	s8,3674e <main-0x11fc98b2>
  cc:	6961                	lui	s2,0x18
  ce:	736e                	ld	t1,248(sp)
  d0:	7369722f          	.insn	4, 0x7369722f
  d4:	34367663          	bgeu	a2,gp,420 <main-0x11fffbe0>
  d8:	652d                	lui	a0,0xb
  da:	666c                	ld	a1,200(a2)
  dc:	752d                	lui	a0,0xfffeb
  de:	7562                	ld	a0,56(sp)
  e0:	746e                	ld	s0,248(sp)
  e2:	2d75                	addiw	s10,s10,29 # 1901d <main-0x11fe6fe3>
  e4:	3432                	fld	fs0,296(sp)
  e6:	302e                	fld	ft0,232(sp)
  e8:	2d34                	fld	fa3,88(a0)
  ea:	2d636367          	.insn	4, 0x2d636367
  ee:	696e                	ld	s2,216(sp)
  f0:	6c746867          	.insn	4, 0x6c746867
  f4:	2d79                	addiw	s10,s10,30
  f6:	3032                	fld	ft0,296(sp)
  f8:	3532                	fld	fa0,296(sp)
  fa:	302e                	fld	ft0,232(sp)
  fc:	33302e37          	lui	t3,0x33302
 100:	6e2d                	lui	t3,0xb
 102:	6769                	lui	a4,0x1a
 104:	7468                	ld	a0,232(s0)
 106:	796c                	ld	a1,240(a0)
 108:	62696c2f          	.insn	4, 0x62696c2f
 10c:	6363672f          	.insn	4, 0x6363672f
 110:	7369722f          	.insn	4, 0x7369722f
 114:	34367663          	bgeu	a2,gp,460 <main-0x11fffba0>
 118:	752d                	lui	a0,0xfffeb
 11a:	6b6e                	ld	s6,216(sp)
 11c:	6f6e                	ld	t5,216(sp)
 11e:	652d6e77          	.insn	4, 0x652d6e77
 122:	666c                	ld	a1,200(a2)
 124:	2e35312f          	.insn	4, 0x2e35312f
 128:	2e31                	addiw	t3,t3,12 # b00c <main-0x11ff4ff4>
 12a:	2f30                	fld	fa2,88(a4)
 12c:	6e69                	lui	t3,0x1a
 12e:	64756c63          	bltu	a0,t2,786 <main-0x11fff87a>
 132:	0065                	c.nop	25
 134:	6170                	ld	a2,192(a0)
 136:	696e                	ld	s2,216(sp)
 138:	00682e63          	.insn	4, 0x00682e63
 13c:	6d6f682f          	.insn	4, 0x6d6f682f
 140:	2f65                	addiw	t5,t5,25
 142:	6f64                	ld	s1,216(a4)
 144:	7572                	ld	a0,312(sp)
 146:	2f656863          	bltu	a0,s6,436 <main-0x11fffbca>
 14a:	7270                	ld	a2,224(a2)
 14c:	63656a6f          	jal	s4,56782 <main-0x11fa987e>
 150:	7374                	ld	a3,224(a4)
 152:	636f632f          	.insn	4, 0x636f632f
 156:	6c2f736f          	jal	t1,f7818 <main-0x11f087e8>
 15a:	6269                	lui	tp,0x1a
 15c:	682f0073          	.insn	4, 0x682f0073
 160:	2f656d6f          	jal	s10,56456 <main-0x11fa9baa>
 164:	6f64                	ld	s1,216(a4)
 166:	7572                	ld	a0,312(sp)
 168:	2f656863          	bltu	a0,s6,458 <main-0x11fffba8>
 16c:	7270                	ld	a2,224(a2)
 16e:	63656a6f          	jal	s4,567a4 <main-0x11fa985c>
 172:	7374                	ld	a3,224(a4)
 174:	636f632f          	.insn	4, 0x636f632f
 178:	752f736f          	jal	t1,f78ca <main-0x11f08736>
 17c:	63617073          	csrci	0x636,2
 180:	2f65                	addiw	t5,t5,25
 182:	696c                	ld	a1,208(a0)
 184:	6362                	ld	t1,24(sp)
 186:	6100                	ld	s0,0(a0)
 188:	6372                	ld	t1,280(sp)
 18a:	5f68                	lw	a0,124(a4)
 18c:	63737973          	csrrci	s2,0x637,6
 190:	6c61                	lui	s8,0x18
 192:	2e6c                	fld	fa1,216(a2)
 194:	0068                	addi	a0,sp,12
 196:	69727473          	csrrci	s0,0x697,4
 19a:	676e                	ld	a4,216(sp)
 19c:	682e                	ld	a6,200(sp)
 19e:	7000                	ld	s0,32(s0)
 1a0:	6e61                	lui	t3,0x18
 1a2:	6369                	lui	t1,0x1a
 1a4:	632e                	ld	t1,200(sp)
 1a6:	7400                	ld	s0,40(s0)
 1a8:	7361                	lui	t1,0xffff8
 1aa:	00632e6b          	.insn	4, 0x00632e6b
 1ae:	30747263          	bgeu	s0,t2,4b2 <main-0x11fffb4e>
 1b2:	632e                	ld	t1,200(sp)
 1b4:	6d00                	ld	s0,24(a0)
 1b6:	6961                	lui	s2,0x18
 1b8:	2e6e                	fld	ft8,216(sp)
 1ba:	74730053          	.insn	4, 0x74730053
 1be:	6972                	ld	s2,280(sp)
 1c0:	676e                	ld	a4,216(sp)
 1c2:	632e                	ld	t1,200(sp)
	...

Disassembly of section .debug_frame:

0000000000000000 <.debug_frame>:
   0:	000c                	.insn	2, 0x000c
   2:	0000                	unimp
   4:	ffff                	.insn	2, 0xffff
   6:	ffff                	.insn	2, 0xffff
   8:	7c010003          	lb	zero,1984(sp)
   c:	0c01                	addi	s8,s8,0 # 18000 <main-0x11fe8000>
   e:	0002                	c.slli64	zero
  10:	001c                	.insn	2, 0x001c
	...
  1a:	1200                	addi	s0,sp,288
  1c:	0000                	unimp
  1e:	0000                	unimp
  20:	0040                	addi	s0,sp,4
  22:	0000                	unimp
  24:	0000                	unimp
  26:	0000                	unimp
  28:	0e42                	slli	t3,t3,0x10
  2a:	4c10                	lw	a2,24(s0)
  2c:	0488                	addi	a0,sp,576
  2e:	0281                	addi	t0,t0,0
  30:	000c                	.insn	2, 0x000c
  32:	0000                	unimp
  34:	ffff                	.insn	2, 0xffff
  36:	ffff                	.insn	2, 0xffff
  38:	7c010003          	lb	zero,1984(sp)
  3c:	0c01                	addi	s8,s8,0
  3e:	0002                	c.slli64	zero
  40:	0024                	addi	s1,sp,8
  42:	0000                	unimp
  44:	0030                	addi	a2,sp,8
  46:	0000                	unimp
  48:	0040                	addi	s0,sp,4
  4a:	1200                	addi	s0,sp,288
  4c:	0000                	unimp
  4e:	0000                	unimp
  50:	0082                	c.slli64	ra
  52:	0000                	unimp
  54:	0000                	unimp
  56:	0000                	unimp
  58:	0e4a                	slli	t3,t3,0x12
  5a:	4220                	lw	s0,64(a2)
  5c:	0281                	addi	t0,t0,0
  5e:	0a6c                	addi	a1,sp,284
  60:	42c1                	li	t0,16
  62:	000e                	c.slli	zero,0x3
  64:	0b42                	slli	s6,s6,0x10
  66:	0000                	unimp
  68:	0064                	addi	s1,sp,12
  6a:	0000                	unimp
  6c:	0030                	addi	a2,sp,8
  6e:	0000                	unimp
  70:	00c2                	slli	ra,ra,0x10
  72:	1200                	addi	s0,sp,288
  74:	0000                	unimp
  76:	0000                	unimp
  78:	020c                	addi	a1,sp,256
  7a:	0000                	unimp
  7c:	0000                	unimp
  7e:	0000                	unimp
  80:	0e42                	slli	t3,t3,0x10
  82:	01b0                	addi	a2,sp,200
  84:	8144                	.insn	2, 0x8144
  86:	5802                	lw	a6,32(sp)
  88:	0488                	addi	a0,sp,576
  8a:	0689                	addi	a3,a3,2
  8c:	0892                	slli	a7,a7,0x4
  8e:	00030a93          	mv	s5,t1
  92:	c801                	beqz	s0,a2 <main-0x11ffff5e>
  94:	c142                	sw	a6,128(sp)
  96:	c94c                	sw	a1,20(a0)
  98:	d242                	sw	a6,36(sp)
  9a:	d342                	sw	a6,164(sp)
  9c:	0e44                	addi	s1,sp,788
  9e:	4200                	lw	s0,0(a2)
  a0:	b00e                	fsd	ft3,32(sp)
  a2:	8101                	c.srli64	a0
  a4:	4c02                	lw	s8,0(sp)
  a6:	0488                	addi	a0,sp,576
  a8:	0689                	addi	a3,a3,2
  aa:	0892                	slli	a7,a7,0x4
  ac:	44020a93          	addi	s5,tp,1088 # 1a440 <main-0x11fe5bc0>
  b0:	c9c8                	sw	a0,20(a1)
  b2:	d3d2                	sw	s4,228(sp)
  b4:	c168                	sw	a0,68(a0)
  b6:	0e4c                	addi	a1,sp,788
  b8:	4200                	lw	s0,0(a2)
  ba:	b00e                	fsd	ft3,32(sp)
  bc:	8101                	c.srli64	a0
  be:	8802                	jr	a6
  c0:	8904                	.insn	2, 0x8904
  c2:	9206                	add	tp,tp,ra
  c4:	9308                	.insn	2, 0x9308
  c6:	6e0a                	ld	t3,128(sp)
  c8:	c9c8                	sw	a0,20(a1)
  ca:	d3d2                	sw	s4,228(sp)
  cc:	0000                	unimp
  ce:	0000                	unimp
  d0:	00a4                	addi	s1,sp,72
  d2:	0000                	unimp
  d4:	0030                	addi	a2,sp,8
  d6:	0000                	unimp
  d8:	02ce                	slli	t0,t0,0x13
  da:	1200                	addi	s0,sp,288
  dc:	0000                	unimp
  de:	0000                	unimp
  e0:	02c4                	addi	s1,sp,324
  e2:	0000                	unimp
  e4:	0000                	unimp
  e6:	0000                	unimp
  e8:	0e42                	slli	t3,t3,0x10
  ea:	4860                	lw	s0,84(s0)
  ec:	0689                	addi	a3,a3,2
  ee:	0281                	addi	t0,t0,0
  f0:	0488                	addi	a0,sp,576
  f2:	92561297          	auipc	t0,0x92561
  f6:	9308                	.insn	2, 0x9308
  f8:	950a                	add	a0,a0,sp
  fa:	960e                	add	a2,a2,gp
  fc:	9810                	.insn	2, 0x9810
  fe:	9414                	.insn	2, 0x9414
 100:	020c                	addi	a1,sp,256
 102:	d25e                	sw	s7,36(sp)
 104:	d342                	sw	a6,164(sp)
 106:	d442                	sw	a6,40(sp)
 108:	d542                	sw	a6,168(sp)
 10a:	d642                	sw	a6,44(sp)
 10c:	d842                	sw	a6,48(sp)
 10e:	c14a                	sw	s2,128(sp)
 110:	c844                	sw	s1,20(s0)
 112:	c942                	sw	a6,144(sp)
 114:	d742                	sw	a6,172(sp)
 116:	0e42                	slli	t3,t3,0x10
 118:	4200                	lw	s0,0(a2)
 11a:	600e                	.insn	2, 0x600e
 11c:	0281                	addi	t0,t0,0 # ffffffff925610f2 <__sheap+0xffffffff8055e0f2>
 11e:	0488                	addi	a0,sp,576
 120:	0689                	addi	a3,a3,2
 122:	0892                	slli	a7,a7,0x4
 124:	0c940a93          	addi	s5,s0,201 # ffffffffffff80c9 <__sheap+0xffffffffedff50c9>
 128:	0e95                	addi	t4,t4,5
 12a:	1096                	slli	ra,ra,0x25
 12c:	14981297          	auipc	t0,0x14981
 130:	9970                	.insn	2, 0x9970
 132:	7016                	.insn	2, 0x7016
 134:	03d9                	addi	t2,t2,22
 136:	0104                	addi	s1,sp,128
 138:	d3d2                	sw	s4,228(sp)
 13a:	d5d4                	sw	a3,44(a1)
 13c:	d8d6                	sw	s5,112(sp)
 13e:	c158                	sw	a4,4(a0)
 140:	c844                	sw	s1,20(s0)
 142:	c94a                	sw	s2,144(sp)
 144:	d742                	sw	a6,172(sp)
 146:	0e42                	slli	t3,t3,0x10
 148:	4200                	lw	s0,0(a2)
 14a:	600e                	.insn	2, 0x600e
 14c:	0281                	addi	t0,t0,0 # 1498112c <__sheap+0x297e12c>
 14e:	0488                	addi	a0,sp,576
 150:	0689                	addi	a3,a3,2
 152:	0892                	slli	a7,a7,0x4
 154:	0c940a93          	addi	s5,s0,201
 158:	0e95                	addi	t4,t4,5
 15a:	1096                	slli	ra,ra,0x25
 15c:	14981297          	auipc	t0,0x14981
 160:	d258                	sw	a4,36(a2)
 162:	d6d5d4d3          	.insn	4, 0xd6d5d4d3
 166:	4cd8                	lw	a4,28(s1)
 168:	0892                	slli	a7,a7,0x4
 16a:	0c940a93          	addi	s5,s0,201
 16e:	0e95                	addi	t4,t4,5
 170:	1096                	slli	ra,ra,0x25
 172:	1498                	addi	a4,sp,608
 174:	6602                	ld	a2,0(sp)
 176:	1699                	addi	a3,a3,-26
 178:	0024                	addi	s1,sp,8
 17a:	0000                	unimp
 17c:	0030                	addi	a2,sp,8
 17e:	0000                	unimp
 180:	0592                	slli	a1,a1,0x4
 182:	1200                	addi	s0,sp,288
 184:	0000                	unimp
 186:	0000                	unimp
 188:	0028                	addi	a0,sp,8
 18a:	0000                	unimp
 18c:	0000                	unimp
 18e:	0000                	unimp
 190:	0e42                	slli	t3,t3,0x10
 192:	4a60                	lw	s0,84(a2)
 194:	1281                	addi	t0,t0,-32 # 1498113c <__sheap+0x297e13c>
 196:	c158                	sw	a4,4(a0)
 198:	0e42                	slli	t3,t3,0x10
 19a:	0000                	unimp
 19c:	0000                	unimp
 19e:	0000                	unimp
 1a0:	000c                	.insn	2, 0x000c
 1a2:	0000                	unimp
 1a4:	ffff                	.insn	2, 0xffff
 1a6:	ffff                	.insn	2, 0xffff
 1a8:	7c010003          	lb	zero,1984(sp)
 1ac:	0c01                	addi	s8,s8,0
 1ae:	0002                	c.slli64	zero
 1b0:	0024                	addi	s1,sp,8
 1b2:	0000                	unimp
 1b4:	01a0                	addi	s0,sp,200
 1b6:	0000                	unimp
 1b8:	05ba                	slli	a1,a1,0xe
 1ba:	1200                	addi	s0,sp,288
 1bc:	0000                	unimp
 1be:	0000                	unimp
 1c0:	0028                	addi	a0,sp,8
 1c2:	0000                	unimp
 1c4:	0000                	unimp
 1c6:	0000                	unimp
 1c8:	0e42                	slli	t3,t3,0x10
 1ca:	4410                	lw	a2,8(s0)
 1cc:	0488                	addi	a0,sp,576
 1ce:	0281                	addi	t0,t0,0
 1d0:	c15c                	sw	a5,4(a0)
 1d2:	c842                	sw	a6,16(sp)
 1d4:	0e42                	slli	t3,t3,0x10
 1d6:	0000                	unimp
 1d8:	000c                	.insn	2, 0x000c
 1da:	0000                	unimp
 1dc:	ffff                	.insn	2, 0xffff
 1de:	ffff                	.insn	2, 0xffff
 1e0:	7c010003          	lb	zero,1984(sp)
 1e4:	0c01                	addi	s8,s8,0
 1e6:	0002                	c.slli64	zero
 1e8:	0024                	addi	s1,sp,8
 1ea:	0000                	unimp
 1ec:	01d8                	addi	a4,sp,196
 1ee:	0000                	unimp
 1f0:	05e2                	slli	a1,a1,0x18
 1f2:	1200                	addi	s0,sp,288
 1f4:	0000                	unimp
 1f6:	0000                	unimp
 1f8:	0040                	addi	s0,sp,4
 1fa:	0000                	unimp
 1fc:	0000                	unimp
 1fe:	0000                	unimp
 200:	0e42                	slli	t3,t3,0x10
 202:	4660                	lw	s0,76(a2)
 204:	1488                	addi	a0,sp,608
 206:	814c                	.insn	2, 0x814c
 208:	0012                	c.slli	zero,0x4
 20a:	0000                	unimp
 20c:	0000                	unimp
 20e:	0000                	unimp
 210:	001c                	.insn	2, 0x001c
 212:	0000                	unimp
 214:	01d8                	addi	a4,sp,196
 216:	0000                	unimp
 218:	0622                	slli	a2,a2,0x8
 21a:	1200                	addi	s0,sp,288
 21c:	0000                	unimp
 21e:	0000                	unimp
 220:	000c                	.insn	2, 0x000c
 222:	0000                	unimp
 224:	0000                	unimp
 226:	0000                	unimp
 228:	0e42                	slli	t3,t3,0x10
 22a:	4210                	lw	a2,0(a2)
 22c:	0281                	addi	t0,t0,0
 22e:	0000                	unimp
 230:	000c                	.insn	2, 0x000c
 232:	0000                	unimp
 234:	ffff                	.insn	2, 0xffff
 236:	ffff                	.insn	2, 0xffff
 238:	7c010003          	lb	zero,1984(sp)
 23c:	0c01                	addi	s8,s8,0
 23e:	0002                	c.slli64	zero
 240:	0014                	.insn	2, 0x0014
 242:	0000                	unimp
 244:	0230                	addi	a2,sp,264
 246:	0000                	unimp
 248:	062e                	slli	a2,a2,0xb
 24a:	1200                	addi	s0,sp,288
 24c:	0000                	unimp
 24e:	0000                	unimp
 250:	0016                	c.slli	zero,0x5
 252:	0000                	unimp
 254:	0000                	unimp
 256:	0000                	unimp
 258:	0014                	.insn	2, 0x0014
 25a:	0000                	unimp
 25c:	0230                	addi	a2,sp,264
 25e:	0000                	unimp
 260:	0644                	addi	s1,sp,772
 262:	1200                	addi	s0,sp,288
 264:	0000                	unimp
 266:	0000                	unimp
 268:	0012                	c.slli	zero,0x4
 26a:	0000                	unimp
 26c:	0000                	unimp
 26e:	0000                	unimp
 270:	0014                	.insn	2, 0x0014
 272:	0000                	unimp
 274:	0230                	addi	a2,sp,264
 276:	0000                	unimp
 278:	0656                	slli	a2,a2,0x15
 27a:	1200                	addi	s0,sp,288
 27c:	0000                	unimp
 27e:	0000                	unimp
 280:	0022                	c.slli	zero,0x8
 282:	0000                	unimp
 284:	0000                	unimp
 286:	0000                	unimp
 288:	000c                	.insn	2, 0x000c
 28a:	0000                	unimp
 28c:	ffff                	.insn	2, 0xffff
 28e:	ffff                	.insn	2, 0xffff
 290:	7c010003          	lb	zero,1984(sp)
 294:	0c01                	addi	s8,s8,0
 296:	0002                	c.slli64	zero
 298:	001c                	.insn	2, 0x001c
 29a:	0000                	unimp
 29c:	0288                	addi	a0,sp,320
 29e:	0000                	unimp
 2a0:	0678                	addi	a4,sp,780
 2a2:	1200                	addi	s0,sp,288
 2a4:	0000                	unimp
 2a6:	0000                	unimp
 2a8:	0018                	.insn	2, 0x0018
 2aa:	0000                	unimp
 2ac:	0000                	unimp
 2ae:	0000                	unimp
 2b0:	0e42                	slli	t3,t3,0x10
 2b2:	4610                	lw	a2,8(a2)
 2b4:	0281                	addi	t0,t0,0
 2b6:	0000                	unimp
 2b8:	000c                	.insn	2, 0x000c
 2ba:	0000                	unimp
 2bc:	ffff                	.insn	2, 0xffff
 2be:	ffff                	.insn	2, 0xffff
 2c0:	7c010003          	lb	zero,1984(sp)
 2c4:	0c01                	addi	s8,s8,0
 2c6:	0002                	c.slli64	zero
 2c8:	0014                	.insn	2, 0x0014
 2ca:	0000                	unimp
 2cc:	02b8                	addi	a4,sp,328
 2ce:	0000                	unimp
 2d0:	06a8                	addi	a0,sp,840
 2d2:	1200                	addi	s0,sp,288
 2d4:	0000                	unimp
 2d6:	0000                	unimp
 2d8:	0012                	c.slli	zero,0x4
 2da:	0000                	unimp
 2dc:	0000                	unimp
 2de:	0000                	unimp
 2e0:	0014                	.insn	2, 0x0014
 2e2:	0000                	unimp
 2e4:	02b8                	addi	a4,sp,328
 2e6:	0000                	unimp
 2e8:	06ba                	slli	a3,a3,0xe
 2ea:	1200                	addi	s0,sp,288
 2ec:	0000                	unimp
 2ee:	0000                	unimp
 2f0:	0018                	.insn	2, 0x0018
 2f2:	0000                	unimp
 2f4:	0000                	unimp
 2f6:	0000                	unimp
 2f8:	0014                	.insn	2, 0x0014
 2fa:	0000                	unimp
 2fc:	02b8                	addi	a4,sp,328
 2fe:	0000                	unimp
 300:	06d2                	slli	a3,a3,0x14
 302:	1200                	addi	s0,sp,288
 304:	0000                	unimp
 306:	0000                	unimp
 308:	0024                	addi	s1,sp,8
 30a:	0000                	unimp
 30c:	0000                	unimp
 30e:	0000                	unimp
 310:	0014                	.insn	2, 0x0014
 312:	0000                	unimp
 314:	02b8                	addi	a4,sp,328
 316:	0000                	unimp
 318:	06f6                	slli	a3,a3,0x1d
 31a:	1200                	addi	s0,sp,288
 31c:	0000                	unimp
 31e:	0000                	unimp
 320:	001a                	c.slli	zero,0x6
 322:	0000                	unimp
 324:	0000                	unimp
 326:	0000                	unimp
 328:	0014                	.insn	2, 0x0014
 32a:	0000                	unimp
 32c:	02b8                	addi	a4,sp,328
 32e:	0000                	unimp
 330:	0710                	addi	a2,sp,896
 332:	1200                	addi	s0,sp,288
 334:	0000                	unimp
 336:	0000                	unimp
 338:	0012                	c.slli	zero,0x4
 33a:	0000                	unimp
 33c:	0000                	unimp
 33e:	0000                	unimp
 340:	0014                	.insn	2, 0x0014
 342:	0000                	unimp
 344:	02b8                	addi	a4,sp,328
 346:	0000                	unimp
 348:	0722                	slli	a4,a4,0x8
 34a:	1200                	addi	s0,sp,288
 34c:	0000                	unimp
 34e:	0000                	unimp
 350:	0032                	c.slli	zero,0xc
 352:	0000                	unimp
 354:	0000                	unimp
 356:	0000                	unimp
 358:	0014                	.insn	2, 0x0014
 35a:	0000                	unimp
 35c:	02b8                	addi	a4,sp,328
 35e:	0000                	unimp
 360:	0754                	addi	a3,sp,900
 362:	1200                	addi	s0,sp,288
 364:	0000                	unimp
 366:	0000                	unimp
 368:	0032                	c.slli	zero,0xc
 36a:	0000                	unimp
 36c:	0000                	unimp
 36e:	0000                	unimp
 370:	0014                	.insn	2, 0x0014
 372:	0000                	unimp
 374:	02b8                	addi	a4,sp,328
 376:	0000                	unimp
 378:	0786                	slli	a5,a5,0x1
 37a:	1200                	addi	s0,sp,288
 37c:	0000                	unimp
 37e:	0000                	unimp
 380:	0034                	addi	a3,sp,8
 382:	0000                	unimp
 384:	0000                	unimp
	...
