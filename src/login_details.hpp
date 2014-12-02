#ifndef LOGIN_DETAILS_HPP
#define LOGIN_DETAILS_HPP
#include <cppcms/view.h>
#include <cppcms/form.h>

namespace content  {

    struct LoginForm : public cppcms::form  {
    	std::string  userName;
    	std::string  password;
    };


    struct NewUserForm : public cppcms::form  {
    	cppcms::widgets::text  		userName;
    	cppcms::widgets::password  	password;
    	cppcms::widgets::password  	passwordRepeat;
		cppcms::widgets::text  		email;

		NewUserForm() {
			userName.message("Select a  user name")	;
			password.message("Choose a password");
			passwordRepeat.message("Enter password again");
			email.message("Enter your email");

			add(userName);
			add(passwordRepeat);
			add(passwordRepeat);
			add(email);

			userName.non_empty();

		}
    };

    struct LoginPageContent : public cppcms::base_content {
        std::string text;

         LoginForm loginForm;
         NewUserForm newUserForm;
    };

}




#endif // LOGIN_DETAILS_HPP
