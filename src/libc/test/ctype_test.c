
#include <stddef.h>
#include <ctype.h>

#include "test_harness.h"

static const char punctuation[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
static const char spaces[] = " \f\n\r\t\v";
static const int FIRST_CHAR = -128;
static const int LAST_CHAR = 255;

static int is_in(const char *str, int c)
{
    if (c == -1)
    {
        return 0;
    }
    while (*str)
    {
        if (*str == (char)c)
        {
            return 1;
        }
        ++str;
    }
    return 0;
}

TEST_GROUP(ctype)

TEST(ctype, mapper)
{
	/*  -127..-2 ==> 129..255
	 *  -1 (EOF) ==> 0
	 *  0..255   ==> 1..256
	 */
	ASSERT_EQ(130, _ANVIL_CTYPE_RANGE_FIX(-127));
	ASSERT_EQ(255, _ANVIL_CTYPE_RANGE_FIX(-2));
	ASSERT_EQ(0, _ANVIL_CTYPE_RANGE_FIX(-1));
	ASSERT_EQ(1, _ANVIL_CTYPE_RANGE_FIX(0));
	ASSERT_EQ(256, _ANVIL_CTYPE_RANGE_FIX(255));

    END_TEST(ctype);
}

TEST(ctype, isalnum)
{
    int (* volatile ISALNUM)(int c) = isalnum;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if (('0' <= c && c <= '9')
           || ('A' <= c && c <= 'Z')
           || ('a' <= c && c <= 'z')
        )
        {
            ASSERT_NE(0, ISALNUM(c));
        }
        else
        {
            ASSERT_EQ(0, ISALNUM(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, isalpha)
{
    int (* volatile ISALPHA)(int c) = isalpha;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
        {
            ASSERT_NE(0, ISALPHA(c));
        }
        else
        {
            ASSERT_EQ(0, ISALPHA(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, isblank)
{
    int (* volatile ISBLANK)(int c) = isblank;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if (c == ' ' || c == '\t')
        {
            ASSERT_NE(0, ISBLANK(c));
        }
        else
        {
            ASSERT_EQ(0, ISBLANK(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, iscntrl)
{
    int (* volatile ISCNTRL)(int c) = iscntrl;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if ((0 <= c && c <= 0x1f) || (c == 0x7f))
        {
            ASSERT_NE(0, ISCNTRL(c));
        }
        else
        {
            ASSERT_EQ(0, ISCNTRL(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, isdigit)
{
    int (* volatile ISDIGIT)(int c) = isdigit;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if ('0' <= c && c <= '9')
        {
            ASSERT_NE(0, ISDIGIT(c));
        }
        else
        {
            ASSERT_EQ(0, ISDIGIT(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, isgraph)
{
    int (* volatile ISGRAPH)(int c) = isgraph;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if (  ('0' <= c && c <= '9')
           || ('A' <= c && c <= 'Z')
           || ('a' <= c && c <= 'z')
           || is_in(punctuation, c)
        )
        {
            ASSERT_NE(0, ISGRAPH(c));
        }
        else
        {
            ASSERT_EQ(0, ISGRAPH(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, islower)
{
    int (* volatile ISLOWER)(int c) = islower;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if ('a' <= c && c <= 'z')
        {
            ASSERT_NE(0, ISLOWER(c));
        }
        else
        {
            ASSERT_EQ(0, ISLOWER(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, isprint)
{
    int (* volatile ISPRINT)(int c) = isprint;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if (  ('0' <= c && c <= '9')
           || ('A' <= c && c <= 'Z')
           || ('a' <= c && c <= 'z')
           || is_in(punctuation, c)
           || is_in(spaces, c)
        )
        {
            ASSERT_NE(0, ISPRINT(c));
        }
        else
        {
            ASSERT_EQ(0, ISPRINT(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, ispunct)
{
    int (* volatile ISPUNCT)(int c) = ispunct;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if (is_in(punctuation, c))
        {
            ASSERT_NE(0, ISPUNCT(c));
        }
        else
        {
            ASSERT_EQ(0, ISPUNCT(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, isspace)
{
    int (* volatile ISSPACE)(int c) = isspace;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if (is_in(spaces, c))
        {
            ASSERT_NE(0, ISSPACE(c));
        }
        else
        {
            ASSERT_EQ(0, ISSPACE(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, isupper)
{
    int (* volatile ISUPPER)(int c) = isupper;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if ('A' <= c && c <= 'Z')
        {
            ASSERT_NE(0, ISUPPER(c));
        }
        else
        {
            ASSERT_EQ(0, ISUPPER(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, isxdigit)
{
    int (* volatile ISXDIGIT)(int c) = isxdigit;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if (('0' <= c && c <= '9') || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f'))
        {
            ASSERT_NE(0, ISXDIGIT(c));
        }
        else
        {
            ASSERT_EQ(0, ISXDIGIT(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, tolower)
{
    int (* volatile TOLOWER)(int c) = tolower;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if ('A' <= c && c <= 'Z')
        {
            ASSERT_EQ(c - 'A' + 'a', TOLOWER(c));
        }
        else
        {
            ASSERT_EQ(c, TOLOWER(c));
        }
    }
    END_TEST(ctype);
}

TEST(ctype, toupper)
{
    int (* volatile TOUPPER)(int c) = toupper;
    int c;
    for (c = FIRST_CHAR; c <= LAST_CHAR; ++c)
    {
        if ('a' <= c && c <= 'z')
        {
            ASSERT_EQ(c - 'a' + 'A', TOUPPER(c));
        }
        else
        {
            ASSERT_EQ(c, TOUPPER(c));
        }
    }
    END_TEST(ctype);
}

int ctype_test()
{
    CALL_TEST(ctype, mapper);
    CALL_TEST(ctype, isalnum);
    CALL_TEST(ctype, isalpha);
    CALL_TEST(ctype, isblank);
    CALL_TEST(ctype, iscntrl);
    CALL_TEST(ctype, isdigit);
    CALL_TEST(ctype, isgraph);
    CALL_TEST(ctype, islower);
    CALL_TEST(ctype, isprint);
    CALL_TEST(ctype, ispunct);
    CALL_TEST(ctype, isspace);
    CALL_TEST(ctype, isupper);
    CALL_TEST(ctype, isxdigit);
    CALL_TEST(ctype, tolower);
    CALL_TEST(ctype, toupper);

    END_TEST_GROUP(ctype);
}
