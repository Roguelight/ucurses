#pragma once
#include <ucurses/component/Component.hpp>
#include <ucurses/component/menu_template.hpp>
#include <string>

namespace ucurses {

    struct Item
    {
        Item(const std::string& id);

        void Check();
        std::string String();
        size_t length() const;

        bool checked;
        std::string id;
    };

    class Checklist : public menu_template<Item>, public Component
    {
        public:

			Checklist(Window* host, coord x = 0, coord y = 0);

            void checkSelected();
			virtual void bindDefault();

            std::function<void()> onRefresh;
            // Overridden functions call onRefresh()
			void selectNext();
			void selectPrevious();

            const std::string& getSelectedText() const;

		protected:

			virtual void Draw();
			virtual void Process(int input);
    };


}
