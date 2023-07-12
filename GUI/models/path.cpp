#include "path.h"

Path::Path()
{

}



Path::Path(int mId, QList<QGeoCoordinate> mPoints, QString mColor){
    this->mId = mId;
    this->mPoints = mPoints;
    this->mColor = mColor;
}
