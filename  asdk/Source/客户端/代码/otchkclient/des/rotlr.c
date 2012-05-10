/*****************************************************************
 *	�ļ���		��rotlr.c
 *	�ļ�����	����λ��������	
 *	�����		��	
 *	����ʱ��	: 2002/05/27
 *	�汾		: 1.0
 *	------------------------------	
 *		ʱ��			�޸���		ע��	
 *		2002/05/27		Wu Qing		��������	
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

