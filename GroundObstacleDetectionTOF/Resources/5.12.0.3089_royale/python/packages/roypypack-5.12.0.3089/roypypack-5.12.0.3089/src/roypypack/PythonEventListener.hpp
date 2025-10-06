/****************************************************************************\
 * Copyright (C) 2022 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#pragma once

#include <royale/IEvent.hpp>
#include <royale/IEventListener.hpp>

namespace royale {
class PythonEventListener : public royale::IEventListener {
  public:
    ROYALE_API virtual ~PythonEventListener() {
    }

    ROYALE_API void onEvent(std::unique_ptr<royale::IEvent> &&event) {
        onEventPython(event->severity(), event->describe().toStdString(), event->type());
    }

    ROYALE_API virtual void onEventPython(royale::EventSeverity severity, const std::string description, royale::EventType type) = 0;
};
} // namespace royale
