#include <jfc/wanikani_reviews_icon/icons.h>

#include <mutex>

static const struct {
  guint  	 width;
  guint  	 height;
  guint  	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  guint8 	 pixel_data[32 * 32 * 4 + 1];
} graphic = {
  32, 32, 4,
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\367\367\001\367\367\367"
  "\071\367\367\367w\367\367\367\240\367\367\367\304\367\367\367\314\367\367"
  "\367\313\367\365\366\264\367\367\367\221\367\366\367[\367\363\365\027\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\367\365\366\023\367\367\367\202\364\366\367\346\341\361\372\377\314\353"
  "\374\377\275\350\375\377\257\345\377\377\254\344\377\377\254\344\377\377"
  "\265\346\376\377\303\351\375\377\326\356\373\377\353\363\370\376\367\367"
  "\367\271\367\367\367H\367\367\367\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\367\367\367\001\367\364\366t\361\365\370\361\320\354\373\377\260\345\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\275\350\375\377\341\361\372\377\367\367\367\302\367"
  "\367\367)\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\367\367\024\367\366\366\277\332\357\372"
  "\377\260\345\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\301\351\375\377\356\364\370\366\367\366\367"
  "a\374\060\266\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\367\367\367\035\364\366\367\333\307\352\374\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\260\345\377\377\344\362\371"
  "\377\367\365\366{]]]\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\367\367\367\022\364\366\367\332\301\351\375\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\253"
  "\341\373\377\260\231\233\377\245\217\216yv*&\003\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\370a\300\002\367\365\366\274\310\352\374\377\254\344\377\377"
  "\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344"
  "\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377"
  "\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344"
  "\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377"
  "\254\344\377\377\254\344\377\377\247\245\264\377\346Q\063\377\272\067\"\335"
  "r\027\017I\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\364\366k\335\360\372\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\237\311\341\377\241\313\343"
  "\377\321Y:\377\352[E\377\334P\066\371\220'\030u\000\000\000\000\000\000\000\000\367\367\367"
  "\016\362\366\370\355\261\345\376\377\254\344\377\377\254\344\377\377\254\344"
  "\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377"
  "\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344"
  "\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377"
  "\254\344\377\377\254\344\377\377\254\344\377\377\243\321\352\377\261\205"
  "\212\377\234\221\234\377\254\343\376\377\327mG\377\336Q<\377\340Y@\377\332"
  "O\065\371g\022\015\064\000\000\000\000\367\367\367t\324\355\373\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\245"
  "\325\356\377\326D/\377\335oH\377\237\256\300\377\254\343\376\377\306hM\377"
  "\366L.\377\341N\065\377\365`C\377d\014\007d\367\367\367\000\365\367\367\332\263"
  "\345\376\377\254\344\377\377\254\344\377\377\254\344\377\377\251\340\372"
  "\377\235\321\350\377\236\321\351\377\251\340\372\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\253"
  "\343\375\377\253\342\375\377\300gg\377\356S;\377\341mF\377\234\263\307\377"
  "\246\330\361\377\344vO\377\336G,\377\361S:\377\360\\@\377\252\063\040\255\367"
  "\355\362+\344\362\371\377\254\344\377\377\254\344\377\377\234\317\346\377"
  "y\242\217\377s\232+\377l\231\030\377`\216\012\377_\215\014\377p\236v\377\207"
  "\267\273\377\232\315\343\377\254\344\377\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\254\344\377\377\216\274\320\377e\214u\377]\203\025\377"
  "Y|\027\377\207i\032\377\263=#\377\326lE\377\257\261\301\377\247\317\347\377"
  "\317^<\377\365L.\377\356U>\377\353`H\377\273:%\306\367\366\366f\322\355\373"
  "\377\254\344\377\377\216\274\317\377^\206#\377y\250\035\377t\245\030\377Mq"
  "\007\377Ms\005\377S|\005\377e\227\007\377]\213\006\377V\177'\377\247\335\365\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377y\243\246\377a\221\007\377d\223"
  "\010\377c\220\015\377{\251!\377{\253\040\377ix\021\377\270W\066\377\263\252\267"
  "\377\273\246\257\377\343iC\377\370M/\377\350U?\377\363^B\377~\034\021u\367"
  "\367\367\223\302\351\375\377\237\323\353\377Ik.\377j\235\011\377l\236\013\377"
  "j\234\010\377e\226\007\377d\225\006\377r\221R\377i\234\007\377i\234\007\377h\204L"
  "\377n\235m\377\214\273\313\377\223\303\330\377x\243\241\377g\231\007\377i\234"
  "\010\377j\235\010\377j\235\011\377n\231\031\377\235\232G\377\212\215\204\377"
  "\257R\062\377\325mG\377\342sJ\377\354R\063\377\370M/\377\362V=\377\357S\067"
  "\377f\017\013S\367\367\367\246\262\335\362\377n\226\214\377b\220\012\377i\234"
  "\007\377i\234\007\377i\234\007\377i\234\007\377g\232\007\377^\214\006\377i\234\007\377"
  "i\234\007\377i\234\007\377i\234\007\377d\224\007\377\\\211\006\377f\230\007\377j\235"
  "\010\377k\236\012\377j\235\011\377c\220\023\377\274\264\233\377\373\320}\377"
  "\206q@\377\234-\032\377\350jD\377\346T\064\377\370M/\377\352O\070\377\355P\067"
  "\377\306RE\377\303\267\267\066\367\367\367\267q\227D\377m\237\016\377i\234"
  "\010\377f\230\007\377`\216\006\377i\234\007\377i\234\007\377i\234\007\377i\234\007\377"
  "i\234\007\377i\234\007\377i\234\010\377l\236\013\377o\241\020\377p\242\021\377m\237"
  "\015\377m\231/\377\212\236s\377\256\250s\377\264\241x\377\333\264n\377\321"
  "\253f\377w:\033\377\302<$\377\370N\060\377\370P\062\377\370O\061\377\353Q\071"
  "\377\267\066!\377\324\335\344\377\367\367\367\065\367\365\366\257\205\255N"
  "\377i\234\007\377i\234\007\377{\227&\377\250\244k\377h\223\060\377b\222\006\377"
  "_\216\005\377c\223\005\377i\234\007\377e\210\033\377\206\232o\377\206\240k\377y"
  "\231M\377\206\235E\377\271\253V\377\332\272\200\377\335\271u\377\353\303"
  "y\377\372\314{\377\304\240_\377pC\040\377\240\062\035\377\333D)\377\370O\061"
  "\377\370P\062\377\357[D\377\340VB\377\222BA\377\334\356\370\377\367\367\367"
  "\064\367\367\367\232\227\266x\377i\234\007\377i\234\007\377\325\276c\377\332\271"
  "\177\377\272\252\215\377\266\245\205\377\300\262\231\377\313\271\232\377"
  "\335\266k\377\361\304v\377\336\273\177\377\326\265|\377\314\260\200\377\347"
  "\301}\377\375\317}\377\364\307x\377\350\274r\377\313\246c\377\214k<\377\204"
  "\064\031\377\242\062\036\377\315?&\377\370M/\377\370P\062\377\363R\065\377\350"
  "P\066\377\230@<\377\244\323\354\377\342\361\371\377\367\367\367#\367\367\367"
  "t\260\305\235\377i\235\010\377i\234\007\377\347\305n\377\377\317}\377\370\312"
  "y\377\375\315|\377\371\313z\377\372\313z\377\377\317}\377\377\317}\377\377"
  "\317}\377\377\317}\377\363\305w\377\316\250e\377\240\206U\377\223\234\227"
  "\377|\200\203\377\221\060\032\377\242\062\036\377\252\064\037\377\337E*\377\370"
  "M/\377\370N\060\377\361P\063\377\340^L\377\256\066\040\377\230\264\311\377\254"
  "\344\377\377\355\364\370\371\367\367\367\001\367\367\367@\314\324\305\377a"
  "\220\006\377i\234\007\377\344\304l\377\377\317}\377\373\314{\377\357\303u\377"
  "\377\317}\377\377\317}\377\377\317}\377\376\316|\377\353\277s\377\305\240"
  "`\377\215\207r\377\223\271\310\377\246\332\363\377\221\203\221\377\240-\033"
  "\377\240\061\035\377\307=%\377\364L.\377\370M/\377\370M/\377\370M/\377\323"
  "N:\377\250\064\040\377\224\240\262\377\254\344\377\377\265\346\376\377\367"
  "\367\367\302\000\000\000\000\367\367\367\004\356\360\354\357\262\256O\377\343\303k"
  "\377\377\317}\377\377\317}\377\377\317}\377\340\267m\377\315\251c\377\251"
  "\213Q\377\240\204M\377rb\066\377\201\235\245\377\224\305\332\377\253\343\376"
  "\377\254\344\377\377\222\220\240\377\256\065\040\377\363K.\377\275\067!\377"
  "\312>%\377\370M/\377\366L.\377\360L\060\377\331I\062\377\250@\067\377\232\262"
  "\306\377\254\344\377\377\254\344\377\377\317\354\374\377\367\367\367|\000\000"
  "\000\000\000\000\000\000\367\367\367\230\313\273\242\377\277\236\\\377\313\246b\377\321"
  "\252e\377\327\257h\377\311\244a\377\206p?\377\205U.\377\265?$\377\242\205"
  "\223\377\247\332\363\377\234\303\332\377\230\272\320\377\221\243\265\377"
  "\262\066\040\377\365M/\377\370M/\377\366L/\377\316>&\377\332A'\377\340I\061"
  "\377\253=-\377\231\215\234\377\244\323\354\377\254\344\377\377\254\344\377"
  "\377\254\344\377\377\352\363\370\376\367\367\367\037\000\000\000\000\000\000\000\000\367\367"
  "\367)\344\340\337\376\213H.\377\215N\061\377\213T\064\377\210V\064\377\220h"
  ">\377\223h?\377\213\033\017\377\303\017\010\377\323C\063\377\333F-\377\356S\067"
  "\377\366V\071\377\235-\033\377\330E+\377\370O\061\377\370M/\377\343S>\377\337"
  "\\L\377\235\061\037\377\215\225\246\377\247\332\364\377\254\344\377\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\305\352\375\377\367\367\367"
  "\252\002\002\002\000\000\000\000\000\000\000\000\000\000\000\000\000\367\367\367\234\331\261\247\377\251"
  "Z:\377\241V\070\377\241V\070\377\243V\070\377\241@(\377\236\060\035\377\257\065"
  "\040\377\352H,\377\366L.\377\365L.\377\355I-\377\224*\031\377\313?&\377\362"
  "K.\377\330P=\377\264<)\377\221hq\377\232\277\326\377\254\343\376\377\254"
  "\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\256\344\377"
  "\377\355\364\370\371\367\367\367'\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\365"
  "\366\021\366\362\360\344\263}m\377\241V\070\377\236T\066\377\247W\071\377\227"
  "\067\"\377\231-\032\377\226KK\377\224\061$\377\230-\033\377\232-\033\377\252\062"
  "\036\377\226,\032\377\203AC\377\251w\200\377\232\235\257\377\235\305\334\377"
  "\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344"
  "\377\377\254\344\377\377\254\344\377\377\331\357\372\377\367\367\367}\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\367\367;\353\344\342\367"
  "\244dP\377\226@(\377\226\060\035\377\224\060\035\377\277\070\"\377\255z\203\377"
  "\234\303\331\377\251\334\366\377\243\320\351\377\242\317\347\377\246\326"
  "\360\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377"
  "\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344"
  "\377\377\254\344\377\377\315\353\374\377\367\367\367\267\367\367\367\002\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\367\367O\350\340"
  "\336\371\234[U\377\225+\031\377\223*\030\377\225,\032\377\271<%\377\311C+\377"
  "\222\245\267\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344"
  "\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377"
  "\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\315\353"
  "\374\377\366\367\367\304\367\367\367\013\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\367\367D\355\351\351\361\271\207"
  "\204\377\252\063\037\377\303:#\377\206u\201\377\211<:\377\313K\071\377\241\315"
  "\345\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377"
  "\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344"
  "\377\377\260\345\377\377\333\357\372\377\367\367\367\263\367\367\367\012\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\367\367\367#\367\367\367\303\322\307\306\377\240_[\377\306"
  "D\066\377\213\222\242\377\276:#\377\255\230\244\377\254\344\377\377\254\344"
  "\377\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344\377\377"
  "\254\344\377\377\254\344\377\377\312\353\374\377\356\364\370\365\367\367"
  "\367u\367\367\367\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\367\367\000\367\367"
  "\367Z\366\365\364\324\362\321\317\377\277\305\317\377\236JC\377\340pe\377"
  "\250\334\366\377\254\344\377\377\254\344\377\377\254\344\377\377\254\344"
  "\377\377\273\347\376\377\324\355\373\377\356\364\370\371\367\367\367\234"
  "\367\367\367\037\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\367\367\367\000\367\367\367<\367\367\367\212\367\366\366\311\347\343"
  "\343\370\345\356\364\377\337\360\372\377\341\361\372\377\351\363\371\377"
  "\363\366\367\343\367\367\367\257\367\367\367h\367\361\365\024\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
};

GdkPixbuf *jfc::get_init_image()
{
    static GdkPixbuf *pixbuf;
    static std::once_flag flag;

    std::call_once(flag, []()
    {
        pixbuf = gdk_pixbuf_new_from_data(
           graphic.pixel_data, //ptr to beginning of data
           GDK_COLORSPACE_RGB, //data has rgb channels (redundant, since enum only has 1 value)
           TRUE, //data has an alpha channel
           8, //each channel has 8 bits (hence rgba32)
           graphic.width, //width in pixels
           graphic.height, //height in pixels
           4 * graphic.width, //stride (row length in bytes: 1 byte per channel * 4 channels * width in pixels)
           nullptr, //destroy functor, use to add user defined clean up
           nullptr //user data for destroy functor
        );
    });

    return pixbuf; 
}
