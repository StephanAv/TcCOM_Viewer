#ifndef TCCOM_OBJECTMODEL_H
#define TCCOM_OBJECTMODEL_H

#include <QAbstractItemModel>
#include <optional>
#include <vector>
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
    CTCID class_id; // 0 - 15
    uint32_t otcid; // 16 - 19
    uint32_t parent; // 20 - 23
    uint32_t refCnt; // 24 - 27
    uint32_t state; // 28 - 31 (8 ^0 OP, 4 ^= SafeOp, 2 ^= PreOp)
    uint32_t unknown_a; // 32 - 35
    uint32_t unknown_b; // 36 - 39;
    uint32_t unknown_c; // 40 - 43;
    uint32_t unknown_d; // 44 - 47;
    std::string name; // Name: 48 - 176

    TcComModule(uint8_t *data);

    std::shared_ptr<TcComModule> pParent;
};
#pragma pack(pop)

class TcCOM_ObjectModel : public QAbstractItemModel
{
    //Q_OBJECT
    static constexpr long m_port = 10;
public:
    TcCOM_ObjectModel(const QString& amsNetId);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    //Qt::ItemFlags flags(const QModelIndex &index) const override;
//    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;
//    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
//    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;


    std::vector<std::shared_ptr<TcComModule>> m_root;
private:
    AmsAddr					m_amsAddr = {};
    long					m_clientPort = 0;
    uint32_t                m_nTcComModules = 0;
};

#endif // TCCOM_OBJECTMODEL_H
