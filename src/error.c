/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 10:45:54 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/12 19:36:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		throw_error(char *e)
{
	ft_putstr_fd(e, 1);
	ft_putchar_fd('\n', 1);
	return (1);
}