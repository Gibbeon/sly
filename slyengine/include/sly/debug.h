#ifdef _DEBUG

#define SYSTEM_HALT(message) THROW(message)
#define PAUSE() system("cmd /C pause")
#define TODO(message) printf("TODO at " FILE_LINE "\n\t" message)
#define NYI() TODO("Not yet implemented")
#define HALT(message) SYSTEM_HALT("HALT at " FILE_LINE "\n\t" message)
#define BOUNDS_CHECK(max, index) index < 0 || index >= max ? HALT("Failed Assert BOUNDS_CHECK - " TOSTRING(index) " is out of bounds max " TOSTRING(MAX)) : index
#define NOT_NULL(x) (x) == NULL ? HALT(STRINGIFY(x) " is NULL\n\t") : (x)

#define SLYASSERT_TRUE(condition, message) (condition) == TRUE ? (void(0)) : HALT("'" STRINGIFY(condition) "' expected TRUE, but is FALSE\n\t" message)
#define SLYASSERT_NOTNULL(condition, message) (condition) != NULL ? (void(0)) : HALT("'" STRINGIFY(condition) "' expected NOT NULL, but is NULL" "\n\t" message)
#define SLYASSERT_GT(condition, value, message) (condition) > (value) ? (void(0)) : HALT("'" STRINGIFY(condition) "' expected greater than value, but value=''\n\t" message)
#define SLYASSERT_GE(condition, value, message) (condition) >= (value) ? (void(0)) : HALT("'" STRINGIFY(condition) "' expected greater or equal value, but value=''\n\t" message)

#else

#define PAUSE() system("cmd /C pause")
#define TODO(message) NOOP()
#define HALT(message) NOOP()
#define BOUNDS_CHECK(max, index) NOOP()
#define NOT_NULL(x) NOOP()
#define NYI() NOOP()
#define SYSTEM_HALT(message) NOOP()

#define SLYASSERT_TRUE(condition, message) NOOP()
#define SLYASSERT_NOTNULL(condition, message) NOOP()
#define SLYASSERT_GT(condition, value, message) NOOP()
#define SLYASSERT_GE(condition, value, message) NOOP()

#endif
