#pragma once

#include <tuple>
#include <functional>
#include <vector>

namespace Engine
{
	class GenericQueuedEvent
	{
	public:
		typedef void(*FlushCallback)();

		virtual void Invoke() const {}

		static void RegisterQueue(FlushCallback flushCallback)
		{
			RegisteredQueues.push_back(flushCallback);
		}

		static void Flush()
		{
			for (int i = 0; i < (int)RegisteredQueues.size(); ++i)
				RegisteredQueues[i]();

			RegisteredQueues.clear();
		}

	private:
		static inline std::vector<FlushCallback> RegisteredQueues = std::vector<FlushCallback>();
	};

	template <typename... Arguments>
	class QueuedEvent : public GenericQueuedEvent
	{
	public:
		void Invoke() const override
		{
			std::apply(Callback, EventArguments);
		}

		static void Queue(const std::function<Arguments...>& callback, const Arguments&... arguments)
		{
			if (QueuedEvents.empty())
				GenericQueuedEvent::RegisterQueue(&Flush);
				
			QueuedEvents.push_back(QueuedEvent<Arguments...>(callback, arguments));
		}

		static void Flush()
		{
			for (int i = 0; i < (int)RegisteredQueues.size(); ++i)
				QueuedEvents[i]();

			QueuedEvents.clear();
		}

	private:
		typedef std::vector<QueuedEvent<Arguments...>> EventQueue;

		std::tuple<Arguments...> EventArguments;
		std::function<void(Arguments...)> Callback;

		QueuedEvent(const std::function<Arguments...>& callback, const Arguments&... arguments) : Callback(callback), EventArguments(std::make_tuple(arguments...)) {}

		static inline EventQueue QueuedEvents = EventQueue();
	};

	template <typename... Arguments>
	class Event
	{
	public:
		typedef std::function<void(Arguments...)> EventCallback;

		void Fire(const Arguments&... arguments);
		void FireAsync(const Arguments&... arguments);
		void Connect(const EventCallback& callback);
		void Wait(const EventCallback& callback);

	private:
		int EventId = -1;

		struct InternalEvent
		{
			EventCallback Callback;
		};
	};
}