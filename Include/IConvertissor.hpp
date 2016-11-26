#ifndef ICONVERTISSOR_HPP_
# define ICONVERTISSOR_HPP_

namespace Convertissor
{
    template <typename T, typename U>
    class IConvertissor
    {
        public :
            virtual ~IConvertissor() { }
            virtual void setConvertissorMode(int) = 0;
            virtual int getConvertissorMode() const = 0;
            virtual T convert(const U&) const = 0;
    };
}

#endif /*! ICONVERTISSOR_HPP_ */