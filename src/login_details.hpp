#ifndef LOGIN_DETAILS_HPP
#define LOGIN_DETAILS_HPP
#include <cppcms/view.h>
#include <cppcms/form.h>
#include <string>


namespace content  {

    struct LoginForm : public cppcms::form  {
        cppcms::widgets::text       userName;
        cppcms::widgets::password   password;

        static const std::string formName;

        LoginForm() {
            userName.message("User name");
            password.message("Password");

            add(userName);
            add(password);
            userName.non_empty();
            password.non_empty();
        }
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
         LoginForm loginForm;
         NewUserForm newUserForm;
    };

}




#endif // LOGIN_DETAILS_HPP
