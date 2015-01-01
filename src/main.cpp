#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <cppcms/view.h>
#include <cppcms/form.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "login_details.hpp"

//====================================


const std::string content::LoginForm::formName = "LoginForm";

//====================================

class homesecApp : public cppcms::application {
public:
    homesecApp(cppcms::service &srv);
    void loginFormHander();
    void serve_file(std::string file_name);

};

//=======================================

homesecApp::homesecApp(cppcms::service &srv) :
            cppcms::application(srv) {

    dispatcher().assign("/static/([a-z_0-9\\.]+\\.css)", &homesecApp::serve_file,this,1);
    mapper().assign("static", "/static/{1}");

    dispatcher().assign("", &homesecApp::loginFormHander, this);
    mapper().assign("");

    mapper().root("/homesec");
}

//=========================================

void homesecApp::serve_file(std::string file_name) {
    std::ifstream f(("static/" + file_name).c_str());

    if (!f) { // Debugging
        f.open(("src/static/" + file_name).c_str());
    }

    if (!f) {
        response().status(404);
        response().out() << "Not found";
    } else {
        response().content_type("application/octet-stream");
        response().set_header("Content-Disposition", "inline");
        response().out() << f.rdbuf();
    }
}

//=======================================

void homesecApp::loginFormHander()
{
    if(request().request_method()=="POST") {
        if (! request().http_form().compare(content::LoginForm::formName)) {

        }
    }

   content::LoginPageContent c;
   render("LoginPageContent",c);
}



int main(int argc, char **argv) {
   try {
   cppcms::service srv(argc,argv);

   srv.applications_pool().mount(
     cppcms::applications_factory<homesecApp>()
   );

   srv.run();

   } catch(std::exception const &e) {
       std::cerr<<e.what()<<std::endl;
   }

   return 0;
}

