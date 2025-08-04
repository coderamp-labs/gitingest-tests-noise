#include "HelloWorld.h"
#include <sstream>
#include <iomanip>
#include <regex>

namespace ModernHelloWorld {

    // ============================================================================
    // IMessageFormatter Implementations
    // ============================================================================

    std::string SimpleFormatter::format(const std::string& message) const {
        return message;
    }

    std::string DecoratedFormatter::format(const std::string& message) const {
        std::stringstream ss;
        std::string border(message.length() + 4, '=');
        
        ss << "\n" << border << "\n";
        ss << "= " << message << " =\n";
        ss << border << "\n";
        
        return ss.str();
    }

    std::string AnimatedFormatter::format(const std::string& message) const {
        animateText(message);
        return message;
    }

    void AnimatedFormatter::animateText(const std::string& text) const {
        std::cout << "\n";
        
        // Typewriter effect
        for (char c : text) {
            std::cout << c << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        std::cout << "\n";
        
        // Blinking effect
        for (int i = 0; i < 3; ++i) {
            std::cout << "\r" << std::string(text.length(), ' ') << "\r" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << text << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        
        std::cout << "\n";
    }

    // ============================================================================
    // MessageFactory Implementation
    // ============================================================================

    std::unique_ptr<IMessageFormatter> MessageFactory::createFormatter(MessageType type) {
        switch (type) {
            case MessageType::SIMPLE:
                return std::make_unique<SimpleFormatter>();
            case MessageType::DECORATED:
                return std::make_unique<DecoratedFormatter>();
            case MessageType::ANIMATED:
                return std::make_unique<AnimatedFormatter>();
            default:
                return std::make_unique<DecoratedFormatter>();
        }
    }

    // ============================================================================
    // ConfigManager Implementation
    // ============================================================================

    ConfigManager& ConfigManager::getInstance() {
        static ConfigManager instance;
        return instance;
    }

    void ConfigManager::setDelay(int milliseconds) {
        delay_ms_ = std::max(0, milliseconds);
    }

    int ConfigManager::getDelay() const {
        return delay_ms_;
    }

    void ConfigManager::setMessage(const std::string& message) {
        message_ = message;
    }

    std::string ConfigManager::getMessage() const {
        return message_;
    }

    void ConfigManager::setFormatterType(MessageFactory::MessageType type) {
        formatter_type_ = type;
    }

    MessageFactory::MessageType ConfigManager::getFormatterType() const {
        return formatter_type_;
    }

    // ============================================================================
    // HelloWorldApp Implementation
    // ============================================================================

    HelloWorldApp::HelloWorldApp() {
        // Constructor initializes the application with default settings
    }

    void HelloWorldApp::run() {
        try {
            std::cout << "🚀 Starting Modern Hello World Application...\n";
            
            initialize();
            createFormatter();
            displayMessage();
            cleanup();
            
            std::cout << "✅ Application completed successfully!\n";
        } catch (const std::exception& e) {
            std::cerr << "❌ Error: " << e.what() << std::endl;
        }
    }

    void HelloWorldApp::initialize() {
        std::cout << "📋 Initializing application components...\n";
        
        validateConfiguration();
        
        // Simulate initialization delay
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        std::cout << "✅ Initialization complete!\n";
    }

    void HelloWorldApp::displayMessage() {
        auto& config = ConfigManager::getInstance();
        std::string message = config.getMessage();
        
        std::cout << "\n🎯 Displaying message:\n";
        
        if (config.getFormatterType() == MessageFactory::MessageType::ANIMATED) {
            // For animated formatter, we need to handle it specially
            formatter_->format(message);
        } else {
            std::string formatted = formatter_->format(message);
            std::cout << formatted << std::endl;
        }
        
        performDelay();
    }

    void HelloWorldApp::cleanup() {
        std::cout << "🧹 Performing cleanup operations...\n";
        
        // Simulate cleanup operations
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        std::cout << "✅ Cleanup complete!\n";
    }

    void HelloWorldApp::createFormatter() {
        auto& config = ConfigManager::getInstance();
        formatter_ = MessageFactory::createFormatter(config.getFormatterType());
        
        std::cout << "🔧 Created formatter of type: ";
        switch (config.getFormatterType()) {
            case MessageFactory::MessageType::SIMPLE:
                std::cout << "Simple";
                break;
            case MessageFactory::MessageType::DECORATED:
                std::cout << "Decorated";
                break;
            case MessageFactory::MessageType::ANIMATED:
                std::cout << "Animated";
                break;
        }
        std::cout << "\n";
    }

    void HelloWorldApp::validateConfiguration() const {
        auto& config = ConfigManager::getInstance();
        
        if (config.getDelay() < 0) {
            throw std::invalid_argument("Delay cannot be negative");
        }
        
        if (config.getMessage().empty()) {
            throw std::invalid_argument("Message cannot be empty");
        }
        
        std::cout << "✅ Configuration validation passed!\n";
    }

    void HelloWorldApp::performDelay() const {
        auto& config = ConfigManager::getInstance();
        int delay = config.getDelay();
        
        if (delay > 0) {
            std::cout << "⏳ Waiting for " << delay << "ms...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }

    // ============================================================================
    // StringUtils Implementation
    // ============================================================================

    std::string StringUtils::toUpperCase(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    std::string StringUtils::toLowerCase(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    std::string StringUtils::reverse(const std::string& str) {
        return std::string(str.rbegin(), str.rend());
    }

    bool StringUtils::isAlphabetic(const std::string& str) {
        return std::all_of(str.begin(), str.end(), ::isalpha);
    }

    std::string StringUtils::generateRandomString(size_t length) {
        static const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, chars.size() - 1);
        
        std::string result;
        result.reserve(length);
        
        for (size_t i = 0; i < length; ++i) {
            result += chars[dis(gen)];
        }
        
        return result;
    }

} // namespace ModernHelloWorld

// ============================================================================
// Main Function
// ============================================================================

int main() {
    using namespace ModernHelloWorld;
    
    std::cout << "🌟 Welcome to the Modern C++ Hello World Application! 🌟\n";
    std::cout << "This application demonstrates various modern C++ features:\n";
    std::cout << "• Design Patterns (Strategy, Factory, Singleton)\n";
    std::cout << "• Modern C++ features (smart pointers, lambdas, etc.)\n";
    std::cout << "• Threading and synchronization\n";
    std::cout << "• Exception handling\n";
    std::cout << "• RAII and resource management\n\n";
    
    // Configure the application
    auto& config = ConfigManager::getInstance();
    config.setMessage("Hello, Modern C++ World!");
    config.setDelay(1000);
    config.setFormatterType(MessageFactory::MessageType::DECORATED);
    
    // Create and run the application
    HelloWorldApp app;
    app.run();
    
    // Demonstrate some utility functions
    std::cout << "\n🔧 Demonstrating utility functions:\n";
    std::string testString = "Hello World";
    std::cout << "Original: " << testString << "\n";
    std::cout << "Uppercase: " << StringUtils::toUpperCase(testString) << "\n";
    std::cout << "Lowercase: " << StringUtils::toLowerCase(testString) << "\n";
    std::cout << "Reversed: " << StringUtils::reverse(testString) << "\n";
    std::cout << "Is alphabetic: " << (StringUtils::isAlphabetic(testString) ? "Yes" : "No") << "\n";
    std::cout << "Random string: " << StringUtils::generateRandomString(10) << "\n";
    
    std::cout << "\n🎉 Thank you for using the Modern C++ Hello World Application!\n";
    
    return 0;
} 