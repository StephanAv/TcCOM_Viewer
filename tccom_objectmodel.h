#ifndef TCCOM_OBJECTMODEL_H
#define TCCOM_OBJECTMODEL_H

#include <QAbstractItemModel>
#include <optional>
#include <Windows.h>
#include "TcAdsDef.h"
#include "TcAdsAPI.h"

#pragma pack(push, 1)
struct CTCID {
    uint32_t data1; // 4
    uint16_t data2; // 2
    uint16_t data3; // 2
    uint16_t data4; // 2
    uint8_t  data5[6]; // 6
}; // 16 byte


struct TcComModule {
    CTCID class_id;
    uint16_t state;
    uint16_t refCnt;
};
#pragma pack(pop)

class TcCOM_ObjectModel //: public QAbstractItemModel
{
    //Q_OBJECT
    static constexpr long m_port = 10;
public:
    TcCOM_ObjectModel(const QString& amsNetId);

    //std::shared_ptr<>
private:
    AmsAddr					m_amsAddr = {};
    long					m_clientPort = 0;
    uint32_t                m_nTcComModules = 0;
};

#endif // TCCOM_OBJECTMODEL_H
