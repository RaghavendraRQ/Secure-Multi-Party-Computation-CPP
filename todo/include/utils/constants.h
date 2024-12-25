//
// Created by raghavendra on 11/30/24.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace CONSTANTS {
    namespace SMPCConstants {
        inline constexpr int MODULUS = 65537;
        inline constexpr unsigned SHARE_COUNT = 3;
        inline constexpr unsigned THRESHOLD = 3;
    }

    namespace TestConstants {
        inline constexpr unsigned MODULUS = 1048576;
        inline constexpr unsigned SHARE_COUNT = 5;
        inline constexpr unsigned THRESHOLD = 5;
    }

    using namespace SMPCConstants;
}

#endif //CONSTANTS_H
