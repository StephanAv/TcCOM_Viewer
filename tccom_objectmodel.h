#ifndef TCCOM_OBJECTMODEL_H
#define TCCOM_OBJECTMODEL_H

#include <QAbstractItemModel>
#include <optional>

class TcCOM_ObjectModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    TcCOM_ObjectModel(const QString& amsNetId);

    //std::shared_ptr<>
};

#endif // TCCOM_OBJECTMODEL_H
