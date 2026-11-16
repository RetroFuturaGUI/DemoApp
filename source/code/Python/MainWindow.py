import RetroFuturaGuiBinding

class MainWindow:
    def __init__(self, binding):
        self.binding = binding
        self.setup()

    def onButtonClick(self):
        print("This is a function written in Python!")

    def setup(self):
        # Widgets are named by their full path. window, scene, container, widget
        self.binding.ConnectSlot("SecondaryWindow/ScrollViewScene/RootContainer/TestButton", self.onButtonClick, self.binding.WidgetAction.OnClick, False)
