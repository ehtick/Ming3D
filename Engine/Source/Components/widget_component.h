#pragma once

#include "component.h"
#include "GUI/widget_render_object.h"

namespace Ming3D
{
    class Widget;

    enum class EWidgetRenderMode
    {
        World,
        Overlay
    };

    class WidgetComponent : public Component
    {
        DEFINE_CLASS(Ming3D::WidgetComponent, Ming3D::Component)

    private:
        static void InitialiseClass();

        WidgetRenderObject* mRenderObject = nullptr;
        Widget* mWidget = nullptr;
        WidgetTree* mWidgetTree = nullptr;
        EWidgetRenderMode mRenderMode = EWidgetRenderMode::World;

    public:
        WidgetComponent();
        ~WidgetComponent();
        virtual void InitialiseComponent();

        virtual void Tick(float inDeltaTime) override;

        void SetWidget(Widget* widget);
        void SetRenderMode(EWidgetRenderMode renderMode);
    };
}
