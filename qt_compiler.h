#ifndef QT_COMPILER_H
#define QT_COMPILER_H

#if defined(__MINGW32__)

typedef quint8  uint8_t;
typedef quint16 uint16_t;
typedef quint32 uint32_t;
typedef quint64 uint64_t;

typedef qint8  int8_t;
typedef qint16 int16_t;
typedef qint32 int32_t;
typedef qint64 int64_t;

typedef float  float32_t;
typedef double float64_t;

#else

#endif

#endif // QT_COMPILER_H
