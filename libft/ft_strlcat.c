/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:08:59 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/24 17:00:16 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	i = 0;
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (dst[i] != '\0')
		i++;
	while (i < dstsize - 1 && src[i - dst_len] != '\0')
	{
		dst[i] = src[i - dst_len];
		i++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}

/*
int	main(void)
{
    char dest[20] = "ABCDE";
    char src[] = "1234";
   
	//xがdest文字数以下の時
	unsigned int result3 = strlcat(NULL, src, 2); //retrun value = src_len
		+ destszie          
	printf("aaa\n");
	printf("%s: %u\n",dest,result3);
	// printf("%u",result3);

    //xが(dast文字数＋str文字数)以下の時
	// unsigned int result4 = ft_strlcat(dest, src, 7); //retrun value = src_len
		+ dst_len    dst = ABCDE1(szie - 1 - dst_len word)
	// printf("%s: %u\n",dest,result4);

	//xがdestの文字数+srcの文字数より大きい時の時
	// unsigned int result6 = strlcat(dest, src, 15);  //retrun value = src_len
		+ dst_len   dst = ABCDE1234(dst + src)
	// printf("%s: %u\n",dest,result6);
    return(0);
}*/
