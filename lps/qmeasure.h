#ifndef QMEASURE_H
#define QMEASURE_H
#include "sm_config.h"
#include "qbeacon.h"
#include <QMetaType>
class QMeasure {
public:
  static QMeasure createMeasure(const QBeacon_ptr &beacon, float distance,
                                float rssi);
  QMeasure() = default;
  QMeasure(const QMeasure &measure);
  ~QMeasure() = default;
  inline QBeacon_ptr beacon() const { return m_beacon; }
  inline float measure() const { return m_measure; }
  inline float rssi() const { return m_rssi; }
  inline bool operator<(const QMeasure &entry) const {
    return m_measure < entry.m_measure;
  }
  inline bool operator>(const QMeasure &entry) const {
    return !(*this < entry);
  }
  inline bool operator==(const QMeasure &entry) const {
    return (m_beacon->id() == entry.m_beacon->id())
            && sm::float_compare(m_measure,entry.m_measure)
            && sm::float_compare(m_rssi, entry.m_rssi);
  }
  inline bool operator!=(const QMeasure &entry) const {
    return !(*this == entry);
  }
  void setBeacon(const QBeacon_ptr &beacon);
  void setMeasure(float measure);
  void setRSSI(float rssi);

private:
  QBeacon_ptr m_beacon{nullptr};
  float m_measure{0.f};
  float m_rssi{0.f};
};

inline uint qHash(const QMeasure &f) { return qHash(f.beacon()->uuid()); }
Q_DECLARE_METATYPE(QMeasure)
#endif // QMEASURE_H
