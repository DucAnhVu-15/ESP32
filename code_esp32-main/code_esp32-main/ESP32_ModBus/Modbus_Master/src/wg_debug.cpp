#include "wg_debug.h"


time_t now;

/**
 * @brief Logs an error message to the debug log.
 *
 * This function logs an error message to the debug log, along with a timestamp indicating when
 * the error occurred. The error message is passed as a parameter to the function.
 *
 * @param str The error message to be logged.
 */
void DebugLogger::DebugError(const char *str)
{
    #if ENA_LIB_LOG
        char DebugErrorStr[128];
        sprintf(DebugErrorStr, "%s", str);
        PLOG_ERROR << DebugErrorStr;
    #else
        printf("!!!!!!!!!!!(Error: %s)!!!!!!!!!!!\n", str);
    #endif
}

/**
 * @brief Logs a status message to the debug log.
 *
 * This function logs a status message to the debug log, along with a timestamp indicating when
 * the message was received. The status message is passed as a parameter to the function.
 *
 * @param str The status message to be logged.
 */
void DebugLogger::DebugStatus(const char *str)
{
    #if ENA_LIB_LOG
        char DebugErrorStr[128];
        sprintf(DebugErrorStr, "%s", str);
        PLOG_DEBUG << DebugErrorStr;
    #else
        printf("|||||||||||||(Status: %s)|||||||||||||\n", str);
    #endif
}

/**
 * @brief Logs a custom message to the debug log.
 *
 * This function logs a custom message to the debug log, along with a timestamp indicating when
 * the message was received. The message consists of a header integer value and a vector of strings
 * representing the content of the message. The function formats the message into a single string
 * before logging it to the debug log.
 *
 * @param header An integer value representing the type or category of the message.
 * @param content A vector of strings representing the content of the message.
 */
void DebugLogger::DebugLOG(int header, std::vector<std::string> content) 
{
    #if ENA_LIB_LOG
        switch (header) 
        {
            #if DEBUG_SENSOR
                case SENSOR_DATA:
                    PLOG_DEBUG << "----------------------------------------------------------------";
                    PLOG_DEBUG << "----------------------------------------------------------------";
                    PLOG_DEBUG << "SENSOR_DATA";
                    for (int i = 0; i < content.size(); i++) {
                        PLOG_DEBUG << content[i];
                    }
                break;
            #endif

            #if DEBUG_DEVICE
                case DEVICE_DATA:
                    PLOG_DEBUG << "----------------------------------------------------------------";
                    PLOG_DEBUG << "----------------------------------------------------------------";
                    PLOG_DEBUG << "DEVICE_DATA";
                    for (int i = 0; i < content.size(); i++) {
                        PLOG_DEBUG << content[i];
                    }
                break;
            #endif

            #if DEBUG_PIN
                case PIN_DATA:
                    PLOG_DEBUG << "----------------------------------------------------------------";
                    PLOG_DEBUG << "----------------------------------------------------------------";
                    PLOG_DEBUG << "PIN DATA";
                    for (int i = 0; i < content.size(); i++) {
                        PLOG_DEBUG << content[i];
                    }
                break;
            #endif

            #if DEBUG_MQTT
                case MQTT_PROTOCOL:
                    PLOG_DEBUG << "----------------------------------------------------------------";
                    PLOG_DEBUG << "----------------------------------------------------------------";
                    PLOG_DEBUG << "MQTT PROTOCOL";
                    for (int i = 0; i < content.size(); i++) {
                        PLOG_DEBUG << content[i];
                    }
                break;
            #endif

            #if DEBUG_CONTROL
                case CONTROLLER:
                    PLOG_DEBUG << "----------------------------------------------------------------";
                    PLOG_DEBUG << "----------------------------------------------------------------";
                    PLOG_DEBUG << "CONTROLLER";
                    for (int i = 0; i < content.size(); i++) {
                        PLOG_DEBUG << content[i];
                    }
            #endif

            default:
                break;
        }

    #else
        // std::cout << "----------------------------------------------------------------" << std::endl;
        // std::cout << "----------------------------------------------------------------" << std::endl;
        // now = time(0);
        // std::cout << "Time: " << now << "---";
        switch (header) 
        {
            #if DEBUG_SENSOR
                case SENSOR_DATA:
                    std::cout << "----------------------------------------------------------------" << std::endl;
                    std::cout << "----------------------------------------------------------------" << std::endl;
                    now = time(0);
                    std::cout << "Time: " << now << "---";
                    std::cout << "SENSOR_DATA" << std::endl;
                    for (int i = 0; i < content.size(); i++) {
                        std::cout << content[i] << std::endl;
                    }
                break;
            #endif

            #if DEBUG_DEVICE
                case DEVICE_DATA:
                    std::cout << "----------------------------------------------------------------" << std::endl;
                    std::cout << "----------------------------------------------------------------" << std::endl;
                    now = time(0);
                    std::cout << "Time: " << now << "---";
                    std::cout << "DEVICE_DATA" << std::endl;
                    for (int i = 0; i < content.size(); i++) {
                        std::cout << content[i] << std::endl;
                    }
                break;
            #endif

            #if DEBUG_PIN
                case PIN_DATA:
                    std::cout << "----------------------------------------------------------------" << std::endl;
                    std::cout << "----------------------------------------------------------------" << std::endl;
                    now = time(0);
                    std::cout << "Time: " << now << "---";
                    std::cout << "PIN DATA" << std::endl;
                    for (int i = 0; i < content.size(); i++) {
                        std::cout << content[i] << std::endl;
                    }
                break;
            #endif

            #if DEBUG_MQTT
                case MQTT_PROTOCOL:
                    std::cout << "----------------------------------------------------------------" << std::endl;
                    std::cout << "----------------------------------------------------------------" << std::endl;
                    now = time(0);
                    std::cout << "Time: " << now << "---";
                    std::cout << "MQTT PROTOCOL" << std::endl;
                    for (int i = 0; i < content.size(); i++) {
                        std::cout << content[i] << std::endl;
                    }
                break;
            #endif

            #if DEBUG_CONTROL
                case CONTROLLER:
                    std::cout << "----------------------------------------------------------------" << std::endl;
                    std::cout << "----------------------------------------------------------------" << std::endl;
                    now = time(0);
                    std::cout << "Time: " << now << "---";
                    std::cout << "CONTROLLER" << std::endl;
                    for (int i = 0; i < content.size(); i++) {
                        std::cout << content[i] << std::endl;
                    }
            #endif

            default:
                break;
        }
    #endif
}
