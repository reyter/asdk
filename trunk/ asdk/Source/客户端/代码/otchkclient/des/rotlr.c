/*****************************************************************
 *	文件名		：rotlr.c
 *	文件功能	：移位操作函数	
 *	编程者		：	
 *	初作时间	: 2002/05/27
 *	版本		: 1.0
 *	------------------------------	
 *		时间			修改者		注释	
 *		2002/05/27		Wu Qing		初期作成	
*****************************************************************/
    unsigned int _rotl_self(unsigned int value, int shift)
    {
        register unsigned hibit;
        register unsigned num = value;

        shift &= 0x1f;

        while (shift--)
        {
            hibit = num & 0x80000000;
            num <<= 1;
            if (hibit)
                num |= 1;
        }

        return num;
    }

    unsigned int _rotr_self(unsigned int value, int shift)
    {
        register unsigned lobit;
        register unsigned num = value;

        shift &= 0x1f;

        while (shift--)
        {
             lobit = num & 1;
             num >>= 1;
             if (lobit)
	    	 num |= 0x80000000;
        }

        return num;
    }

