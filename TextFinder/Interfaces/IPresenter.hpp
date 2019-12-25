#ifndef IPRESENTER_HPP
#define IPRESENTER_HPP

namespace interfaces {
    class IPresenter {
        public:
            virtual ~IPresenter() = default;
            virtual void update() noexcept = 0;
    };
}
#endif // IPRESENTER_HPP
