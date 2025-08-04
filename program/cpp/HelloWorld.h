#pragma once

#include <string>
#include <memory>
#include <functional>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <future>
#include <mutex>
#include <condition_variable>

namespace ModernHelloWorld {

    /**
     * @brief Interface for message formatting strategies
     * 
     * This interface defines the contract for different message formatting
     * strategies, following the Strategy design pattern.
     */
    class IMessageFormatter {
    public:
        virtual ~IMessageFormatter() = default;
        virtual std::string format(const std::string& message) const = 0;
    };

    /**
     * @brief Simple message formatter
     * 
     * Provides basic message formatting without additional decorations.
     */
    class SimpleFormatter : public IMessageFormatter {
    public:
        std::string format(const std::string& message) const override;
    };

    /**
     * @brief Decorated message formatter
     * 
     * Adds decorative elements around the message for enhanced presentation.
     */
    class DecoratedFormatter : public IMessageFormatter {
    public:
        std::string format(const std::string& message) const override;
    };

    /**
     * @brief Animated message formatter
     * 
     * Creates animated text effects using timing and character manipulation.
     */
    class AnimatedFormatter : public IMessageFormatter {
    public:
        std::string format(const std::string& message) const override;
    private:
        void animateText(const std::string& text) const;
    };

    /**
     * @brief Message factory for creating different types of messages
     * 
     * Implements the Factory pattern to create various message types
     * based on configuration or user preferences.
     */
    class MessageFactory {
    public:
        enum class MessageType {
            SIMPLE,
            DECORATED,
            ANIMATED
        };

        static std::unique_ptr<IMessageFormatter> createFormatter(MessageType type);
    };

    /**
     * @brief Configuration manager for the Hello World application
     * 
     * Manages application settings and provides a centralized configuration
     * system using the Singleton pattern.
     */
    class ConfigManager {
    public:
        static ConfigManager& getInstance();
        
        void setDelay(int milliseconds);
        int getDelay() const;
        
        void setMessage(const std::string& message);
        std::string getMessage() const;
        
        void setFormatterType(MessageFactory::MessageType type);
        MessageFactory::MessageType getFormatterType() const;

    private:
        ConfigManager() = default;
        ~ConfigManager() = default;
        ConfigManager(const ConfigManager&) = delete;
        ConfigManager& operator=(const ConfigManager&) = delete;

        int delay_ms_ = 100;
        std::string message_ = "Hello, World!";
        MessageFactory::MessageType formatter_type_ = MessageFactory::MessageType::DECORATED;
    };

    /**
     * @brief Main Hello World application class
     * 
     * Orchestrates the entire Hello World application using multiple
     * design patterns and modern C++ features.
     */
    class HelloWorldApp {
    public:
        HelloWorldApp();
        ~HelloWorldApp() = default;

        /**
         * @brief Runs the Hello World application
         * 
         * This method orchestrates the entire application flow:
         * 1. Initializes the application
         * 2. Creates the appropriate message formatter
         * 3. Formats and displays the message
         * 4. Performs cleanup operations
         */
        void run();

        /**
         * @brief Sets up the application environment
         * 
         * Initializes various components and validates configuration.
         */
        void initialize();

        /**
         * @brief Displays the formatted message
         * 
         * Uses the configured formatter to display the message
         * with appropriate timing and effects.
         */
        void displayMessage();

        /**
         * @brief Performs cleanup operations
         * 
         * Ensures proper resource cleanup and application shutdown.
         */
        void cleanup();

    private:
        std::unique_ptr<IMessageFormatter> formatter_;
        std::mutex display_mutex_;
        std::condition_variable display_cv_;
        bool ready_to_display_ = false;

        /**
         * @brief Creates the message formatter based on configuration
         * 
         * Uses the factory pattern to create the appropriate formatter.
         */
        void createFormatter();

        /**
         * @brief Validates the current configuration
         * 
         * Ensures all configuration parameters are within valid ranges.
         */
        void validateConfiguration() const;

        /**
         * @brief Performs a graceful delay
         * 
         * Uses modern C++ timing facilities for precise delays.
         */
        void performDelay() const;
    };

    /**
     * @brief Utility class for string operations
     * 
     * Provides various string manipulation utilities using modern C++.
     */
    class StringUtils {
    public:
        /**
         * @brief Converts string to uppercase
         */
        static std::string toUpperCase(const std::string& str);

        /**
         * @brief Converts string to lowercase
         */
        static std::string toLowerCase(const std::string& str);

        /**
         * @brief Reverses a string
         */
        static std::string reverse(const std::string& str);

        /**
         * @brief Checks if string contains only alphabetic characters
         */
        static bool isAlphabetic(const std::string& str);

        /**
         * @brief Generates a random string of specified length
         */
        static std::string generateRandomString(size_t length);
    };

} // namespace ModernHelloWorld 