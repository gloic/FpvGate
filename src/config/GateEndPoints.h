#pragma once

#define BASE_API            "/api/gate"

// Exposed by Gate
#define LISTEN_START        BASE_API "/listen/start"
#define LISTEN_STOP         BASE_API "/listen/stop"

// Exposed by Starter
#define REGISTER            BASE_API "/register"
#define PASSED              BASE_API "/passed"