all:
	g++ key_gen_normal.cpp utils.cpp utils.hpp -o key_gen_normal
	g++ key_gen_timed.cpp  utils.cpp utils.hpp -o key_gen_timed

	@sudo cp ./data/password_sleep_duration        /etc/password_sleep_duration
	@sudo cp ./data/password_allowance_dates       /etc/password_allowance_dates
	@sudo cp ./data/password_allowance_time_of_day /etc/password_allowance_time_of_day
	@echo Done!
