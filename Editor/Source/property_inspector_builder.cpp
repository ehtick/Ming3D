#include "property_inspector_builder.h"

#include "button.h"
#include <typeinfo>

namespace Ming3D
{
    PropertyInspectorBuilder::PropertyInspectorBuilder(NativeUI::Control* inControl)
    {
        mParentControl = inControl;
    }

    void PropertyInspectorBuilder::Text(std::string inText, int inTextSize)
    {
        NativeUI::TextBox* textBox = CreateTextBox(inText, inTextSize, ctrlHeight);
        mCurrHeight += vertPadding;
    }

    void PropertyInspectorBuilder::Space()
    {
        mCurrHeight += vertPadding;
    }

    void PropertyInspectorBuilder::Button(std::string inText, std::function<void()> inCallbback)
    {
        NativeUI::Button* button = CreateButton(inText, 16, ctrlHeight);
        button->RegisterClickCallback(inCallbback);
        mCurrHeight += vertPadding;
    }

    void PropertyInspectorBuilder::PropertyField(Property* inProp, Object* inObject, std::string inName)
    {
        BeginHorizontal();
        const std::string typeName = inProp->GetTypeName();
        const void* valPtr = inProp->GetPropertyHandle()->GetValuePtr(inObject);
        if (typeName == typeid(std::string).name())
        {
            std::string strHeader = inProp->GetPropertyName() + ":";
            std::string* stringPtr = (std::string*)valPtr;
            NativeUI::TextBox* txtHeader = CreateTextBox(strHeader, 14, ctrlHeight);
            NativeUI::TextBox* txtValue = CreateTextBox(*stringPtr, 14, ctrlHeight);
            txtValue->SetReadonly(false);
            txtValue->RegisterTextChangedCallback(
                [valPtr](std::string newString)
            {
                *(std::string*)valPtr = newString; }
            );
            // TODO: on text changed: set property value
            mCurrHeight += vertPadding;
        }
        EndHorizontal();
    }

    NativeUI::Button* PropertyInspectorBuilder::CreateButton(std::string inText, int inFontSize, float inCtrlHeight)
    {
        NativeUI::Button* btn = new NativeUI::Button(mParentControl);
        btn->SetVerticalSizeMode(NativeUI::SizeMode::Absolute);
        btn->SetVerticalPositionMode(NativeUI::SizeMode::Absolute);
        btn->SetHorizontalSizeMode(NativeUI::SizeMode::Relative);
        btn->SetHorizontalPositionMode(NativeUI::SizeMode::Relative);
        btn->SetSize(1.0f, inCtrlHeight);
        btn->SetPosition(0.0f, mCurrHeight);
        btn->SetText(inText.c_str());
        //btn->SetFontSize(inFontSize);
        if (mHorizontalMode)
            mQueueHorizontalControls.push_back(btn);
        else
            mCurrHeight += inCtrlHeight;
        mControls.push_back(btn);
        return btn;
    }

    NativeUI::TextBox* PropertyInspectorBuilder::CreateTextBox(std::string inText, int inFontSize, float inCtrlHeight)
    {
        NativeUI::TextBox* txtBox = new NativeUI::TextBox(mParentControl);
        txtBox->SetVerticalSizeMode(NativeUI::SizeMode::Absolute);
        txtBox->SetVerticalPositionMode(NativeUI::SizeMode::Absolute);
        txtBox->SetHorizontalSizeMode(NativeUI::SizeMode::Relative);
        txtBox->SetHorizontalPositionMode(NativeUI::SizeMode::Relative);
        txtBox->SetSize(1.0f, inCtrlHeight);
        txtBox->SetPosition(0.0f, mCurrHeight);
        txtBox->SetText(inText.c_str());
        txtBox->SetFontSize(inFontSize);
        if (mHorizontalMode)
            mQueueHorizontalControls.push_back(txtBox);
        else
            mCurrHeight += inCtrlHeight;
        mControls.push_back(txtBox);
        return txtBox;
    }

    void PropertyInspectorBuilder::BeginHorizontal()
    {
        mHorizontalMode = true;
    }

    void PropertyInspectorBuilder::EndHorizontal()
    {
        mHorizontalMode = false;
        const size_t numCtrls = mQueueHorizontalControls.size();
        const float ctrlWidth = 1.0f / numCtrls;
        float maxHeight = 0.0f;
        for (size_t iCtrl = 0; iCtrl < numCtrls; iCtrl++)
        {
            NativeUI::Control* ctrl = mQueueHorizontalControls[iCtrl];
            ctrl->SetPosition(ctrlWidth * iCtrl, ctrl->GetPosition().y);
            ctrl->SetSize(ctrlWidth, ctrl->GetSize().y);
            maxHeight = max(maxHeight, ctrl->GetSize().y);
        }
        mQueueHorizontalControls.clear();
    }

    void PropertyInspectorBuilder::Clear()
    {
        // Remove existing controls
        for (NativeUI::Control* ctrl : mControls)
            delete(ctrl);
        mControls.clear();
        mCurrHeight = 0.0f;
    }
}
