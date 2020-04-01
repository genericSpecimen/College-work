% no duplicates in empty list
remove_dup([], []) :- !.

/*
 * if head is a member of tail list, then it's a duplicate,
 * so we don't bother adding it at the moment. Instead, it will
 * be added when the last occurence of this element is encountered,
 * i.e. when head would no longer be a member of the tail.
 *
 * So, ignore the current duplicate and carry on with the tail.
 */
remove_dup([H|T], R) :-
	member(H, T), !,
	remove_dup(T, R).

/*
 * if head is not a member of the tail list,
 * then it's no longer a duplicate, and we add it to the head of R.
 */
remove_dup([H|T], [H|R]) :-
	\+ member(H, T),
	remove_dup(T, R).
	
