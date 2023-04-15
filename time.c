/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:00:22 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/15 17:03:28 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

t_ms clock()
{
	struct timeval 	time;
	long 			usec;
	long 			sec;
	unsigned long	timenow_us;

	gettimeofday(&time, NULL);
	usec = time.tv_usec;
	sec = time.tv_sec;
	timenow_us = sec * 1000000 + usec;
	//printf("sec %ld, usec %ld\n, now %ld", sec, usec, timenow);
	return (timenow_us / 1000);
}
