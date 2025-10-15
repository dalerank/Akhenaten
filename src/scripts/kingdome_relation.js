log_info("akhenaten: images started")

kingdome_relation {
	salary_ranks [0, 2, 5, 8, 12, 20, 30, 40, 60, 80, 100]
	gift_relation_change_first [3, 5, 10]
	gift_relation_change_second [1, 3, 5]
	gift_relation_change_third [0, 1, 3]
	gift_relation_change_last [0, 0, 1]
	months_since_gift_locker : 12
	tribute_not_paid_years_penalty [-3, -3, -5, -8, -8]
	player_salary_above_king_penalty : 1
	player_salary_less_king_promotion : 1
	first_debt_penalty : -5
	second_debt_penalty : -10
	last_debt_rating_cap : 10

	gift_rules [
		{
			id : GIFT_MODEST
			rate : 8
			minimum : 20
		}
		{
			id : GIFT_GENEROUS
			rate : 4
			minimum : 50
		}
		{
			id : GIFT_LAVISH
			rate : 2
			minimum : 100
		}
	]
}
