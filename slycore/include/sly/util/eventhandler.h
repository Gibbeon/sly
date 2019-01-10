/* struct EventArgs {};

template <typename TArgs = EventArgs&>
class EventHandler {
public:
    EventHandler() {}
    virtual ~EventHandler() {}

    EventHandler& operator +=(std::function<void(TArgs)> event) {
        _events.push_back(event);
        return *this;
    }

    EventHandler& operator -=(std::function<void(TArgs)> event) {
        std::remove(_events.begin(), _events.end(), event);
        return *this;
    }

protected:
    std::vector<std::function<void(EventArgs&)>> _events;
}; */