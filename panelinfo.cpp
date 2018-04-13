#include "panelinfo.h"
//#include <QString>
Panelinfo::Panelinfo()
{
   cnnamemap.insert(0, "肝肾");
   cnnamemap.insert(1, "肝功");
   cnnamemap.insert(2, "肾功");
   cnnamemap.insert(3, "电解质");
   cnnamemap.insert(5, "心肌酶");
   cnnamemap.insert(6, "糖脂");
   cnnamemap.insert(7, "综合11");
   cnnamemap.insert(8, "综合2");
   cnnamemap.insert(9, "临床急诊");
   cnnamemap.insert(10, "综合13");
   cnnamemap.insert(11, "综合13+");
   cnnamemap.insert(12, "综合13A");

   cnnamemap.insert(50, "综合诊断");
   cnnamemap.insert(51, "手术前");
   cnnamemap.insert(52, "急重症");
   cnnamemap.insert(55, "健康");
   cnnamemap.insert(57, "电解质");
   cnnamemap.insert(60, "肝肾");
   cnnamemap.insert(61, "肝功");
   cnnamemap.insert(62, "肾功");
   cnnamemap.insert(63, "手术前+");
   cnnamemap.insert(64, "复查两项");
   cnnamemap.insert(65, "复查3项");

   errmap.insert(0, "黄疸");
   errmap.insert(1, "溶血");
   errmap.insert(2, "脂血");
   errmap.insert(3, "0208_1");
   errmap.insert(4, "0209");
   errmap.insert(5, "0210");
   errmap.insert(6, "0211");
//       errmap.insert(7, "黄疸");
   errmap.insert(8, "0215");
   errmap.insert(9, "0216");
   errmap.insert(10, "0214");
   errmap.insert(11, "0213");
   errmap.insert(12, "0217");
   errmap.insert(13, "0218");
   errmap.insert(14, "0219");
   errmap.insert(15, "0208_2");
   errmap.insert(16, "0214_leak");

}
QString Panelinfo::getCNName(qint16 id)
{

    return cnnamemap.value(id);
}
QString Panelinfo::parseError(qint32 errcode)
{
    QString errstring;
    QMapIterator<qint16, QString> i(errmap);
    while (i.hasNext()) {
        i.next();
        if (errcode & (1 << i.key())) {
            errstring.append(i.value());
            if (i.hasNext())
                errstring.append(',');
        }
    }
    return errstring;
}

