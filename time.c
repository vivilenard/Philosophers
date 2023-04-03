/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:00:22 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/03 19:10:23 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

unsigned long clock()
{
	struct timeval 	time;
	long 			usec;
	long 			sec;
	unsigned long	timenow;

	gettimeofday(&time, NULL);
	usec = time.tv_usec;
	sec = time.tv_sec;
	timenow = sec * 1000000 + usec;
	//printf("sec %ld, usec %ld\n, now %ld", sec, usec, timenow);
	return (timenow);
}
