
#include "double_test_data.h"

const struct double_test_data_s base_10_parser_data[] =
{
    { "1234.5678", 0x40934a45, 0x6d5cfaad },
    { ".12345678e4", 0x40934a45, 0x6d5cfaad },
    { "12345678e-4", 0x40934a45, 0x6d5cfaad },
    { ".0012345678e6", 0x40934a45, 0x6d5cfaad },
    { "-1234.5678", 0xc0934a45, 0x6d5cfaad },
    { "-.12345678e4", 0xc0934a45, 0x6d5cfaad },
    { "-12345678e-4", 0xc0934a45, 0x6d5cfaad },
    { "-.0012345678e6", 0xc0934a45, 0x6d5cfaad },
    { "00001234.56780000", 0x40934a45, 0x6d5cfaad },
    { "0000.12345678e00004", 0x40934a45, 0x6d5cfaad },
    { "000012345678e-00004", 0x40934a45, 0x6d5cfaad },
    { "0000.0012345678e00006", 0x40934a45, 0x6d5cfaad },
    { "-00001234.56780000", 0xc0934a45, 0x6d5cfaad },
    { "-0000.12345678e00004", 0xc0934a45, 0x6d5cfaad },
    { "-000012345678e-00004", 0xc0934a45, 0x6d5cfaad },
    { "-0000.0012345678e00006", 0xc0934a45, 0x6d5cfaad },
    { NULL }
};

// This test data comes from the gdtoa package. There was no copyright
// notice in the file itself but the data (in file testnos3) was posted
// by Fred Tydeman to comp.arch.arithmetic on 26 Feb. 1996.
const struct double_test_data_s gdtoa_test_data[] =
{
    { "9e0306", 0x7fa9a202, 0x8368022e },
    { "4e-079", 0x2fa7b6d7, 0x1d20b96c },
    { "7e-261", 0x9eb8d7e, 0x32be6396 },
    { "6e-025", 0x3ae7361c, 0xb863de62 },
    { "7e-161", 0x1eaf7e0d, 0xb3799aa3 },
    { "7e0289", 0x7c1cbb54, 0x7777a285 },
    { "5e0079", 0x507afcef, 0x51f0fb5f },
    { "1e0080", 0x508afcef, 0x51f0fb5f },
    { "7e-303", 0x1333391, 0x31c46f8b },
    { "5e0152", 0x5fa317e5, 0xef3ab327 },
    { "5e0125", 0x5a07a2ec, 0xc414a03f },
    { "2e0126", 0x5a27a2ec, 0xc414a03f },
    { "7e-141", 0x22d5570f, 0x59bd178c },
    { "4e-192", 0x18323ff0, 0x6eea847a },
    { "9e0043", 0x49102498, 0xea6df0c4 },
    { "1e0303", 0x7ed754e3, 0x1cd072da },
    { "95e-089", 0x2dde3cbc, 0x9907fdc8 },
    { "85e0194", 0x689d1c26, 0xdb7d0dae },
    { "69e0267", 0x77c0b7cb, 0x60c994da },
    { "97e-019", 0x3c665dde, 0x8e688ba6 },
    { "37e0046", 0x49d033d7, 0xeca0adef },
    { "74e0046", 0x49e033d7, 0xeca0adef },
    { "61e-099", 0x2bc0ad83, 0x6f269a17 },
    { "53e-208", 0x151b39ae, 0x1909c31b },
    { "93e-234", 0xfc27b2e, 0x4f210075 },
    { "79e-095", 0x2c9a5db8, 0x12948281 },
    { "87e-274", 0x772d36c, 0xf48e7abd },
    { "83e0025", 0x4585747a, 0xb143e353 },
    { "17e-036", 0x38b698cc, 0xdc60015a },
    { "53e0033", 0x47246a34, 0x18629ef6 },
    { "51e-074", 0x30ecd5be, 0xe57763e6 },
    { "63e-022", 0x3bbdc03b, 0x8fd7016a },
    { "839e0143", 0x5e3ae03f, 0x245703e2 },
    { "749e-182", 0x1abf1472, 0x7744c63e },
    { "999e-026", 0x3b282782, 0xafe1869e },
    { "345e0266", 0x77b0b7cb, 0x60c994da },
    { "914e-102", 0x2b5ffc81, 0xbc29f02b },
    { "829e0102", 0x55b7221a, 0x79cdd1d9 },
    { "307e0090", 0x5322d6b1, 0x83fe4b55 },
    { "859e0182", 0x6654374d, 0x8b87ac63 },
    { "283e0085", 0x5216c309, 0x24bab4b },
    { "589e0187", 0x675526be, 0x9c22eb17 },
    { "302e0176", 0x64fdcf7d, 0xf8f573b7 },
    { "604e0176", 0x650dcf7d, 0xf8f573b7 },
    { "761e-244", 0xde03cea, 0x3586452e },
    { "647e0230", 0x7044d64d, 0x4079150c },
    { "755e0174", 0x64a7d931, 0x93f78fc6 },
    { "255e-075", 0x30dcd5be, 0xe57763e6 },
    { "3391e0055", 0x4c159bd3, 0xad46e346 },
    { "4147e-015", 0x3d923d1b, 0x5eb1d778 },
    { "3996e-026", 0x3b482782, 0xafe1869e },
    { "1998e-026", 0x3b382782, 0xafe1869e },
    { "3338e-296", 0x335519a, 0xc5142aab },
    { "1669e-296", 0x325519a, 0xc5142aab },
    { "8699e-276", 0x772d2df, 0x246ecd2d },
    { "5311e0243", 0x73284e91, 0xf4aa0fdb },
    { "7903e-096", 0x2cd07c2d, 0x27a5b989 },
    { "7611e-226", 0x11d19b87, 0x44033457 },
    { "3257e0058", 0x4cb444b3, 0x4a6fb3eb },
    { "6514e0058", 0x4cc444b3, 0x4a6fb3eb },
    { "3571e0263", 0x77462644, 0xc61d41aa },
    { "7142e0263", 0x77562644, 0xc61d41aa },
    { "5311e0242", 0x72f3720e, 0x5d54d97c },
    { "1617e-063", 0x3384c98f, 0xce16152e },
    { "51881e0037", 0x4897d295, 0xdc76da4 },
    { "31441e-118", 0x285ef890, 0xf5de4c86 },
    { "30179e0079", 0x5143e272, 0xa77478e8 },
    { "60358e0079", 0x5153e272, 0xa77478e8 },
    { "63876e-020", 0x3cc70385, 0x6844bdbf },
    { "31938e-020", 0x3cb70385, 0x6844bdbf },
    { "46073e-032", 0x3a42405b, 0x773fbdf3 },
    { "32941e0051", 0x4b757eb8, 0xad52a5c9 },
    { "82081e0041", 0x49770105, 0xdf3d47cb },
    { "38701e-215", 0x1440492a, 0x4a8a37fd },
    { "62745e0047", 0x4ab0c52f, 0xe6dc6a1b },
    { "12549e0048", 0x4ac0c52f, 0xe6dc6a1b },
    { "64009e-183", 0x1af099b3, 0x93b84832 },
    { "89275e0261", 0x77262644, 0xc61d41aa },
    { "75859e0025", 0x46232645, 0xe1ba93f0 },
    { "57533e0287", 0x7c8272ed, 0x2307f56a },
    { "584169e0229", 0x70ad6570, 0x59dc79aa },
    { "940189e-112", 0x29eb99d6, 0x240c1a28 },
    { "416121e0197", 0x6a00fd07, 0xed297f80 },
    { "832242e0197", 0x6a10fd07, 0xed297f80 },
    { "584738e0076", 0x50e8a85e, 0xb277e645 },
    { "933587e-140", 0x241b2487, 0x28b9c117 },
    { "252601e0121", 0x5a2dda59, 0x2e398dd7 },
    { "358423e0274", 0x79f9463b, 0x59b8f2bd },
    { "892771e-213", 0x14f25818, 0xc7294f27 },
    { "410405e0040", 0x49670105, 0xdf3d47cb },
    { "928609e-261", 0xafbe2dd, 0x66200bef },
    { "302276e-254", 0xc55a462, 0xd91c6ab3 },
    { "920657e-023", 0x3c653a99, 0x85dbde6c },
    { "609019e-025", 0x3bf1f99e, 0x11ea0a24 },
    { "252601e0120", 0x59f7e1e0, 0xf1c7a4ac },
    { "654839e-060", 0x34b00e7d, 0xb3b3f242 },
    { "8823691e0130", 0x5c5e597c, 0xb94b7ae },
    { "2920845e0228", 0x709d6570, 0x59dc79aa },
    { "9210917e0080", 0x51fda232, 0x347e6032 },
    { "5800419e-303", 0x26e58ff, 0xa48f4fce },
    { "6119898e-243", 0xee3ecf2, 0x2ea07863 },
    { "3059949e-243", 0xed3ecf2, 0x2ea07863 },
    { "2572231e0223", 0x6f90f73b, 0xe1dff9ad },
    { "5444097e-021", 0x3cf8849d, 0xd33c95af },
    { "5783893e-127", 0x26f7e590, 0x2ce0e151 },
    { "3865421e-225", 0x1295d4fe, 0x53afec65 },
    { "4590831e0156", 0x61b4689b, 0x4a5fa201 },
    { "9181662e0156", 0x61c4689b, 0x4a5fa201 },
    { "5906361e-027", 0x3bbbe45a, 0x312d08a0 },
    { "7315057e0235", 0x7225f0d4, 0x8362a72 },
    { "9088115e0106", 0x5762e51a, 0x84a3c6a0 },
    { "1817623e0107", 0x5772e51a, 0x84a3c6a0 },
    { "44118455e0129", 0x5c4e597c, 0xb94b7ae },
    { "35282041e0293", 0x7e5512d5, 0x273e62e8 },
    { "31279898e-291", 0x5129b01, 0xb6885d36 },
    { "15639949e-291", 0x5029b01, 0xb6885d36 },
    { "27966061e0145", 0x5f955bcf, 0x72fd10f9 },
    { "55932122e0145", 0x5fa55bcf, 0x72fd10f9 },
    { "70176353e-053", 0x36900683, 0xa21de855 },
    { "40277543e-032", 0x3adf29ca, 0xff893b1 },
    { "50609263e0157", 0x622193af, 0xf1f1c8e3 },
    { "66094077e0077", 0x518b37c4, 0xb7928317 },
    { "84863171e0114", 0x59406e98, 0xf5ec8f37 },
    { "89396333e0264", 0x786526f0, 0x61ca9053 },
    { "87575437e-309", 0x16e0732, 0x602056c },
    { "78693511e-044", 0x3870bc7b, 0x7603a2ca },
    { "90285923e-206", 0x16d14700, 0x83f89d48 },
    { "30155207e-030", 0x3b423a4a, 0xd20748a2 },
    { "245540327e0121", 0x5acc569e, 0x968e0944 },
    { "263125459e0287", 0x7d44997a, 0x298b2f2e },
    { "566446538e-257", 0xc64472b, 0xa9550e86 },
    { "283223269e-257", 0xc54472b, 0xa9550e86 },
    { "245540327e0122", 0x5b01b623, 0x1e18c5cb },
    { "491080654e0122", 0x5b11b623, 0x1e18c5cb },
    { "971212611e-126", 0x27a397d3, 0xc9745d2f },
    { "229058583e0052", 0x4c76ce94, 0xfebdc7a5 },
    { "325270231e0039", 0x49cc7ccf, 0x90c9f8ab },
    { "989648089e-035", 0x3a8880a3, 0xd515e849 },
    { "653777767e0273", 0x7a720223, 0xf2b3a881 },
    { "923091487e0209", 0x6d30bc60, 0xe6896717 },
    { "526250918e0288", 0x7d89bfd8, 0xb3edfafa },
    { "350301748e-309", 0x18e0732, 0x602056c },
    { "741111169e-203", 0x17a14fe7, 0xdaf8f3ae },
    { "667284113e-240", 0xff09355, 0xf8050c02 },
    { "1227701635e0120", 0x5abc569e, 0x968e0944 },
    { "9981396317e-182", 0x1c38afe1, 0xa2a66aa },
    { "5232604057e-298", 0x41465b8, 0x96c24520 },
    { "5572170023e-088", 0x2fb08478, 0x22f765b2 },
    { "1964322616e0122", 0x5b31b623, 0x1e18c5cb },
    { "3928645232e0122", 0x5b41b623, 0x1e18c5cb },
    { "8715380633e-058", 0x35f4614c, 0x3219891f },
    { "4856063055e-127", 0x279397d3, 0xc9745d2f },
    { "8336960483e-153", 0x223a06a1, 0x24b95e1 },
    { "1007046393e-155", 0x21a01891, 0xfc4717fd },
    { "5378822089e-176", 0x1d695fd4, 0xc88d4b1b },
    { "5981342308e-190", 0x1a83db11, 0xac608107 },
    { "7214782613e-086", 0x3020b552, 0xd2edcdea },
    { "5458466829e0142", 0x5f70acde, 0x6a98eb4c },
    { "9078555839e-109", 0x2b5fc575, 0x867314ee },
    { "6418488827e0079", 0x526021f1, 0x4ed7b3fa },
    { "65325840981e0069", 0x5081a151, 0xddbd3c4a },
    { "49573485983e0089", 0x54a221bd, 0x871d2cf4 },
    { "46275205733e0074", 0x51830e6c, 0x7d4e3480 },
    { "92550411466e0074", 0x51930e6c, 0x7d4e3480 },
    { "41129842097e-202", 0x1832c3e7, 0x2d179607 },
    { "93227267727e-049", 0x380960fe, 0x8d5847f },
    { "41297294357e0185", 0x688c4943, 0x7fccfadb },
    { "41534892987e-067", 0x343a1266, 0x6477886d },
    { "42333842451e0201", 0x6be0189a, 0x26df575f },
    { "78564021519e-227", 0x13115551, 0x5fd37265 },
    { "53587107423e-061", 0x35800a19, 0xa3ffd981 },
    { "53827010643e-200", 0x18a32fa6, 0x9a69bd6d },
    { "83356057653e0193", 0x6a4544e6, 0xdaee2a18 },
    { "45256834646e-118", 0x29a541ec, 0xdfd48694 },
    { "45392779195e-110", 0x2b4fc575, 0x867314ee },
    { "23934638219e0291", 0x7e81deaf, 0x40ead9a0 },
    { "995779191233e0113", 0x59e2d44e, 0xdcc51304 },
    { "997422852243e-265", 0xb676688, 0xfaee99bc },
    { "653532977297e-123", 0x28d925a0, 0xaabcdc68 },
    { "938885684947e0147", 0x60f11894, 0xb202e9f4 },
    { "619534293513e0124", 0x5c210c20, 0x303fe0f1 },
    { "539879452414e-042", 0x39a5e66d, 0xc3d6bdb5 },
    { "742522891517e0259", 0x782c1c35, 0x2fc3c309 },
    { "254901016865e-022", 0x3dbc06d3, 0x66394441 },
    { "685763015669e0280", 0x7c85fd7a, 0xa44d9477 },
    { "384865004907e-285", 0x72aa65b, 0x58639e69 },
    { "286556458711e0081", 0x5321958b, 0x36c5102b },
    { "573112917422e0081", 0x5331958b, 0x36c5102b },
    { "769525178383e-150", 0x234253ec, 0xe161420 },
    { "416780288265e0192", 0x6a3544e6, 0xdaee2a18 },
    { "226963895975e-111", 0x2b3fc575, 0x867314ee },
    { "665592809339e0063", 0x4f778b65, 0x16c2b478 },
    { "3891901811465e0217", 0x6f99ab82, 0x61990292 },
    { "4764593340755e0069", 0x50e4177a, 0x9915fbf8 },
    { "6336156586177e0269", 0x7a7173f7, 0x6c63b792 },
    { "8233559360849e0095", 0x56566fee, 0x5649a7a },
    { "3662265515198e-107", 0x2c538e6e, 0xdd48f2a3 },
    { "1831132757599e-107", 0x2c438e6e, 0xdd48f2a3 },
    { "7812878489261e-179", 0x1d726dae, 0x7bbeda75 },
    { "6363857920591e0145", 0x60b28a61, 0xcf9483b7 },
    { "8811915538555e0082", 0x53a51f50, 0x8b287ae7 },
    { "9997878507563e-195", 0x1a253db2, 0xfea1ea31 },
    { "9224786422069e-291", 0x634ee5d, 0x56b32957 },
    { "6284426329974e-294", 0x58d3409, 0xdfbca26f },
    { "9199302046091e-062", 0x35c13597, 0x2630774c },
    { "6070482281213e-122", 0x29423fa9, 0xe6fcf47e },
    { "2780161250963e-301", 0x405acc2, 0x53064c2 },
    { "8233559360849e0094", 0x5621f324, 0xd11d4862 },
    { "72027097041701e0206", 0x6d946778, 0x12d3a606 },
    { "97297545286625e0215", 0x6f79ab82, 0x61990292 },
    { "99021992302453e-025", 0x3da5c671, 0x4def374c },
    { "54104687080198e-022", 0x3e373cdf, 0x8db7a7bc },
    { "33519685743233e0089", 0x5537f203, 0x339c9629 },
    { "67039371486466e0089", 0x5547f203, 0x339c9629 },
    { "39064392446305e-180", 0x1d626dae, 0x7bbeda75 },
    { "17796979903653e0261", 0x78e072f3, 0x819c1321 },
    { "28921916763211e0038", 0x4a9eebab, 0xe0957af3 },
    { "87605699161665e0155", 0x6302920f, 0x96e7f9ef },
    { "41921560615349e-067", 0x34d9b2a5, 0xc4041e4b },
    { "80527976643809e0061", 0x4f7c7c5a, 0xea080a49 },
    { "72335858886654e-159", 0x21cce77c, 0x2b3328fc },
    { "52656615219377e0102", 0x57f561de, 0xf4a9ee32 },
    { "15400733123779e-072", 0x33b8bf7e, 0x7fa6f02a },
    { "77003665618895e-073", 0x33a8bf7e, 0x7fa6f02a },
    { "475603213226859e-042", 0x3a42d730, 0x88f4050a },
    { "972708181182949e0116", 0x5b218a7f, 0x36172332 },
    { "246411729980464e-071", 0x342eef5e, 0x1f90ac34 },
    { "123205864990232e-071", 0x341eef5e, 0x1f90ac34 },
    { "609610927149051e-255", 0xe104273, 0xb18918b1 },
    { "475603213226859e-041", 0x3a778cfc, 0xab31064d },
    { "672574798934795e0065", 0x508226c6, 0x84c87261 },
    { "134514959786959e0066", 0x509226c6, 0x84c87261 },
    { "294897574603217e-151", 0x2395f2df, 0x5e675a0f },
    { "723047919080275e0036", 0x4a7eebab, 0xe0957af3 },
    { "660191429952702e-088", 0x30bddc7e, 0x975c5045 },
    { "330095714976351e-088", 0x30addc7e, 0x975c5045 },
    { "578686871093232e-159", 0x21fce77c, 0x2b3328fc },
    { "144671717773308e-159", 0x21dce77c, 0x2b3328fc },
    { "385018328094475e-074", 0x3398bf7e, 0x7fa6f02a },
    { "330095714976351e-089", 0x3077e398, 0x7916a69e },
    { "2215901545757777e-212", 0x171a80a6, 0xe566428c },
    { "1702061899637397e-276", 0x9cacc46, 0x749dccfe },
    { "1864950924021923e0213", 0x6f53ae60, 0x753af6ca },
    { "3729901848043846e0213", 0x6f63ae60, 0x753af6ca },
    { "7487252720986826e-165", 0x20f8823a, 0x57adbef9 },
    { "3743626360493413e-165", 0x20e8823a, 0x57adbef9 },
    { "4988915232824583e0119", 0x5be5f6de, 0x9d5d6b5b },
    { "3771476185376383e0277", 0x7cae3c14, 0xd6916ce9 },
    { "6182410494241627e-119", 0x2a81b964, 0x58445d07 },
    { "2572981889477453e0142", 0x609dfc11, 0xfbf46087 },
    { "7793560217139653e0051", 0x4dd28046, 0x1b856ec5 },
    { "9163942927285259e-202", 0x194fe601, 0x457dce4d },
    { "6353227084707473e0155", 0x63650aff, 0x653ffe8a },
    { "4431803091515554e-211", 0x17609068, 0x4f5fe998 },
    { "9324754620109615e0211", 0x6f0f7d67, 0x21f7f144 },
    { "8870461176410409e0263", 0x79d90529, 0xa37b7e22 },
    { "90372559027740405e0143", 0x612491da, 0xad0ba280 },
    { "18074511805548081e0146", 0x61a011f2, 0xd73116f4 },
    { "54897030182071313e0029", 0x496ec556, 0x66d8f9ec },
    { "76232626624829156e-032", 0x3ccb7738, 0x11e75fe },
    { "59898021767894608e-165", 0x2128823a, 0x57adbef9 },
    { "29949010883947304e-165", 0x2118823a, 0x57adbef9 },
    { "26153245263757307e0049", 0x4d83de00, 0x5bd620df },
    { "27176258005319167e-261", 0xd27c074, 0x7bd76fa1 },
    { "18074511805548081e0147", 0x61d4166f, 0x8cfd5cb1 },
    { "24691002732654881e-115", 0x2b759a27, 0x83ce70ab },
    { "58483921078398283e0057", 0x4f408ce4, 0x99519ce3 },
    { "64409240769861689e-159", 0x22692238, 0xf7987779 },
    { "94080055902682397e-242", 0x11364981, 0xe39e66ca },
    { "31766135423537365e0154", 0x63550aff, 0x653ffe8a },
    { "68985865317742005e0164", 0x657a999d, 0xdec72aca },
    { "13797173063548401e0165", 0x658a999d, 0xdec72aca },
    { "902042358290366539e-281", 0x9522dc0, 0x1ca1cb8c },
    { "238296178309629163e0272", 0x7c038fd9, 0x3f1f5342 },
    { "783308178698887621e0226", 0x72925ae6, 0x2cb346d8 },
    { "439176241456570504e0029", 0x499ec556, 0x66d8f9ec },
    { "899810892172646163e0283", 0x7e6adf51, 0xfa055e03 },
    { "926145344610700019e-225", 0x14f307a6, 0x7f1f69ff },
    { "653831131593932675e0047", 0x4d63de00, 0x5bd620df },
    { "130766226318786535e0048", 0x4d73de00, 0x5bd620df },
    { "557035730189854663e-294", 0x693bfac, 0x6bc4767b },
    { "902042358290366539e-280", 0x986b930, 0x23ca3e6f },
    { "272104041512242479e0200", 0x6d13bbb4, 0xbf05f087 },
    { "544208083024484958e0200", 0x6d23bbb4, 0xbf05f087 },
    { "680429695511221511e0192", 0x6b808ebc, 0x116f8a20 },
    { "308975121073410857e0236", 0x7490db75, 0xcc001072 },
    { "792644927852378159e0078", 0x53d7bff3, 0x36d8ff06 },
    { "783308178698887621e0223", 0x71f2cbac, 0x35f71140 },
    { "8396094300569779681e-252", 0xf8ab223, 0xefcee35a },
    { "3507665085003296281e-074", 0x346b85c0, 0x26a264e4 },
    { "7322325862592278999e0074", 0x5336775b, 0x6caa5ae0 },
    { "6014546754280072926e0209", 0x6f396397, 0xb06732a4 },
    { "7120190517612959703e0120", 0x5cc3220d, 0xcd5899fd },
    { "3507665085003296281e-073", 0x34a13398, 0x18257f0f },
    { "4345544743100783551e-218", 0x168a9c42, 0xe5b6d89f },
    { "9778613303868468131e-090", 0x313146fe, 0x1075e1ef },
    { "7539204280836061195e-082", 0x32d3d969, 0xe3dbe723 },
    { "7862637540082247119e-202", 0x19eaba32, 0x62ee707b },
    { "2176832332097939832e0200", 0x6d43bbb4, 0xbf05f087 },
    { "8643988913946659879e0115", 0x5bbe71ec, 0x1ed0a4f9 },
    { "5529436763613147623e0138", 0x6079c677, 0xbe6f236e },
    { "6764958008109694533e-173", 0x1fed0669, 0x2e6f5ef6 },
    { "6802601037806061975e0197", 0x6cbf92ba, 0xcb3cb40c },
    { "1360520207561212395e0198", 0x6ccf92ba, 0xcb3cb40c },
    { "62259110684423957791e0047", 0x4dcd8f2c, 0xfc20d6e8 },
    { "88800290202542652011e-226", 0x1526cec5, 0x1a43f41a },
    { "41010852717673354694e-221", 0x16201295, 0x4b6aabba },
    { "20505426358836677347e-221", 0x16101295, 0x4b6aabba },
    { "66102447903809911604e0055", 0x4f776206, 0x8a24fd55 },
    { "35600952588064798515e0119", 0x5cb3220d, 0xcd5899fd },
    { "14371240869903838702e0205", 0x6e78d92d, 0x2bcc7a81 },
    { "57500690832492901689e0043", 0x4cf65d3e, 0x2acd616b },
    { "23432630639573022093e-107", 0x2dbdd54c, 0x40a2f25f },
    { "62259110684423957791e0048", 0x4e02797c, 0x1d948651 },
    { "35620497849450218807e-306", 0x475b220, 0x82529425 },
    { "69658634627134074624e0200", 0x6d93bbb4, 0xbf05f087 },
    { "99440755792436956989e-062", 0x37362d10, 0x462a26f4 },
    { "55277197169490210673e0081", 0x54d945bf, 0xa911e32a },
    { "36992084760177624177e-318", 0x1f8c5f9, 0x551c2f9a },
    { "30888265282878466443e-111", 0x2cf01b8e, 0xf28251fc },
    { "5527719716.9490210673e0091", 0x54d945bf, 0xa911e32a },
    { "55277.197169490210673e0096", 0x54d945bf, 0xa911e32a },
    { "552771971694902.10673e0086", 0x54d945bf, 0xa911e32a },

    // # examples of bugs introduced 20001113, fixed 20010207
    // # first is 2^-1075 (half the smallest denormal)
    { "2.4703282292062327208828439643411068618252990130716238221279284125033775363510437593264991818081799618989828234772285886546332835517796989819938739800539093906315035659515570226392290858392449105184435931802849936536152500319370457678249219365623669863658480757001585769269903706311928279558551332927834338409351978015531246597263579574622766465272827220056374006485499977096599470454020828166226237857393450736339007967761930577506740176324673600968951340535537458516661134223766678604162159680461914467291840300530057530849048765391711386591646239524912623653881879636239373280423891018672348497668235089863388587925628302755995657524455507255189313690836254779186948667994968324049705821028513185451396213837722826145437693412532098591327667236328125e-324", 0, 0 },
    { "2.47032822920623272e-324", 0, 0 },
    // # examples reported by Mark Dickinson of bugs in the bigcomp() logic introduced
    // # 20090316 in dtoa.c to speed handling of absurdly long input:
    { "12579816049008305546974391768996369464963024663104e-357", 0x90bbd, 0x7412d19f },
    { "17489628565202117263145367596028389348922981857013e-357", 0xc938e, 0x9000492f },
    { "18487398785991994634182916638542680759613590482273e-357", 0xd4b3a, 0xee198863 },
    { "32002864200581033134358724675198044527469366773928e-358", 0x24d1e, 0xed8448e3 },
    { "99999999999999994487665465554760717039532578546e-47", 0x3ff00000, 0x0 },
    { "1.0000000000000000100000000000000000000001e44", 0x4911efc6, 0x59cf7d4c },
    { "1000000000000000000000000000000000000000e-16", 0x44b52d02, 0xc7e14af6 },
    { "10000000000000000000000000000000000000000e-17", 0x44b52d02, 0xc7e14af6 },
    { "10.900000000000000012345678912345678912345", 0x4025cccc, 0xcccccccd },
    { "104308485241983990666713401708072175773165034278685682646111762292409330928739751702404658197872319129036519947435319418387839758990478549477777586673075945844895981012024387992135617064532141489278815239849108105951619997829153633535314849999674266169258928940692239684771590065027025835804863585454872499320500023126142553932654370362024104462255244034053203998964360882487378334860197725139151265590832887433736189468858614521708567646743455601905935595381852723723645799866672558576993978025033590728687206296379801363024094048327273913079612469982585674824156000783167963081616214710691759864332339239688734656548790656486646106983450809073750535624894296242072010195710276073042036425579852459556183541199012652571123898996574563824424330960027873516082763671875e-1075", 0x78026, 0x65fd9600 },
    { "99037485700245683102805043437346965248029601286431e-373", 0x0, 0x2 },
    { "99617639833743863161109961162881027406769510558457e-373", 0x0, 0x2 },
    { "98852915025769345295749278351563179840130565591462e-372", 0x0, 0x14 },
    { "99059944827693569659153042769690930905148015876788e-373", 0x0, 0x2 },
    { "98914979205069368270421829889078356254059760327101e-372", 0x0, 0x14 },
    { "0.999999999999999999999999999999999999999999999e23", 0x44b52d02, 0xc7e14af6 },
    { "991633793189150720000000000000000000000000000000000000000e-33", 0x44ea3f92, 0x6bad90c6 },
    { "37652435753827922121470370984740152789920e234", 0x78f1667a, 0xc9e75d61 },
    { "999999999999999996790597280027956716285163e-42", 0x3ff00000, 0x0 },
    { "9483973038658180570348795755328802873667739881500874740826641664593613312413122937394311083577538394191754403820631172036846773125424639263833553383990195662207006139342261292777056851379062046720e0", 0x68a03d69, 0x82f2f936 },
    { "20209005503919489280000000000000000000000000000000000000000e-40", 0x43bc0bae, 0x57e880e6 },
    { NULL }
};
