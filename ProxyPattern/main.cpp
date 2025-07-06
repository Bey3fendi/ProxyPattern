#include <iostream>
#include <memory>

#include "ProxyExample.h"
class IPaymentService {
public:
    virtual void PaymentOperation() = 0;

    virtual ~IPaymentService() {

    }
};

class PaymentService : public IPaymentService {
public:
    PaymentService() {

    }
    void PaymentOperation() override {
        std::cout << "Payment is done\n";
    }
};

class ProxyPaymentService : public IPaymentService {
public:
    ProxyPaymentService(std::unique_ptr<IPaymentService> payment_service) : m_payment_service(std::move(payment_service)) {

    }

    void PaymentOperation() override {
        if (CheckAccess()) {
            m_payment_service->PaymentOperation();
        }
    }

private:
    std::unique_ptr<IPaymentService> m_payment_service;

    bool CheckAccess() {
        std::cout << "Access Granted\n";
        return true;
    }

};
//std::unique_ptr<IPaymentService> Ips;
void ClientCode(IPaymentService &ips) {
    ips.PaymentOperation();
}

/*
int main()
{

    //client execute the base client code with payment service
    std::unique_ptr<IPaymentService> ps = std::make_unique<PaymentService>();
    ClientCode(*ps);
    //ps->PaymentOperation();

    std::unique_ptr<ProxyPaymentService> pps = std::make_unique<ProxyPaymentService>(std::move(ps));
    ClientCode(*pps);
    //pps->PaymentOperation();
}
*/

int main() {

    //lets test the ImageViewer class
    Images img{"image1", 1, 1};
    std::unique_ptr<IImageViewer> iv = std::make_unique<ImageViewer>(img);
    std::unique_ptr<IImageViewer> ivp = std::make_unique<ImageViewerProxy>();
    std::string image_name_from_user = "";
    while (true) {
        std::cout << "Dear user please give the image name: \n"; std::cin >> image_name_from_user;
        ivp->DisplayImage(image_name_from_user);
    }
}
