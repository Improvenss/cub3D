/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:53:10 by akaraca           #+#    #+#             */
/*   Updated: 2022/11/04 18:53:10 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @author Ahmet KARACA (akaraca)
 * @author Görkem SEVER (gsever)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/cub3d.h"

int	where_is_my_hero(int *x, int *y, t_main *main)
{
	(*y) = 0;
	while (main->map[*y])
	{
		(*x) = 0;
		while (main->map[*y][*x])
		{
			if (ft_strchr("ENWS", main->map[*y][*x]))
			{
				if (main->map[*y][*x] == 'E')
					main->ply.rotationAngle = 0;
				else if (main->map[*y][*x] == 'N')
					main->ply.rotationAngle = 90;
				else if (main->map[*y][*x] == 'W')
					main->ply.rotationAngle = 180;
				else if (main->map[*y][*x] == 'S')
					main->ply.rotationAngle = 270;
				main->map[*y][*x] = '0';
				return (0);
			}
			(*x)++;
		}
		(*y)++;
	}
	return (0);
}

/**
 * @brief	checking input arguments
 * 
 * @param argc	should be 2 arguments or else -> is error
 * @param map	if map name doesn't have .cub extension -> is error
 * 				if map name size < 5 (for "touch .cub")-> is error
 * 				if the specified file does not exist -> is error
 * @return int : Access 0, Error -1
 */
int	argv_check(int argc, char *map, t_main *main)
{
	int	fd;

	if (argc < 2)
		return (err(RED"Map argument unspecified!"END));
	if (argc > 2)
		return (err(RED"Too many arguments entered!"END));
	if (ft_strcmp_edited(".cub", &map[ft_strlen(map) - 4]) \
		|| ft_strlen(map) < 5 || map[ft_strlen(map) - 5] == '/')
		return (err(RED"Map extension is incorrect!"END));
	fd = open(map, F_OK);
	if (fd == -1)
		return (err(RED"Map argument doesn't exist!"END));
	return (map_check(fd, main));
}

/**
 * @brief 
 * 
* ************************************************************************** *
						✓
Aciklama:
		Birinci şahıs bakış açısıyla bir labirentin içinin "gerçekçi"
	 bir 3D grafik gösterimini oluşturmalısınız. Bu gösterimi daha önce
	 bahsedilen Işın Takibi(Ray Casting) ilkesini kullanarak oluşturmalısınız.

Kısıtlamalar aşağıdaki gibidir:
	• miniLibX kullanmanız gerekiyor. Ya işletim sisteminde bulunan sürümü
 ya da kendi kaynaklarındaki sürümü kullanın. Kaynaklarla çalışmayı seçerseniz,
 libft için yukarıda Ortak Talimatlar bölümünde yazılanlarla aynı kuralları
 uygulamanız gerekir.
	• Pencere kontrolünüz başka bir pencereye geçme, küçültme vb. durumlarda
 akıcı olmalıdır.
	• Duvarın hangi tarafa baktığına (Kuzey, Güney, Doğu, Batı) bağlı olarak
 değişen farklı duvar dokuları sergileyin (seçim sizin).
	• Programınız zemin ve tavan renklerini iki farklı renge
 ayarlayabilmelidir.
	• Program görüntüyü bir pencerede gösterir ve aşağıdaki kurallara uyar:
		◦ Klavyenin sol ve sağ ok tuşları labirentte sola ve sağa bakmanıza
	 izin vermelidir.
		◦ W, A, S ve D tuşları, bakış açısını labirentte hareket ettirmenize
	 izin vermelidir.
		◦ ESC’ye basmak pencereyi kapatmalı ve programdan temiz bir şekilde
	 çıkmalıdır.
		◦ Pencere çerçevesindeki kırmızı çarpı işaretine tıklamak pencereyi
	 kapatmalı ve programdan temiz bir şekilde çıkmalıdır.
		◦ minilibX kullanılması şiddetle önerilmektedir.
	• Programınız ilk argüman olarak bir harita dosyasını .cub
 uzantısıyla almalıdır.
		◦ Harita 6 olası karakterden oluşmalıdır:
			Boş alanlar için 0,
			Duvarlar için 1,
			ve kullanıcının başlangıç pozisyonu
			ve yeniden doğma yönü için N,S,E veya W
			 Basit ve geçerli bir harita örneği:
				111111
				100101
				101001
				1100N1
				111111
		◦ Harita kapalı veya duvarlarla çevrili olmalı, değilse program bir
	 hata vermelidir.
		◦ Harita içeriği dışında, her öğe türü bir veya daha fazla boş
	 satırla ayrılabilir.
		◦ Her zaman en son olması gereken harita içeriği dışında,
	 her öğe türü dosyada herhangi bir sırada ayarlanabilir.
		◦ Harita dışında, bir öğeden gelen her bilgi türü bir veya daha
	 fazla boşlukla ayrılabilir.
		◦ Harita, dosyada göründüğü gibi ayrıştırılmalıdır.
	 Boşluklar haritanın geçerli bir parçasıdır ve işlemek size kalmıştır.
	 Harita kurallarına uyduğu sürece her tür haritayı
	 ayrıştırabilmeniz gerekir.
		◦ Her öğenin (harita hariç) ilk bilgileri, tür tanımlayıcısıdır
	 (bir veya iki karakterden oluşur), ardından her nesne için kesin bir
	 sırayla tüm özel bilgiler gelir, örneğin:
			∗ North texture(Kuzey dokusu):
	Usage: ->	NO ./path_to_the_north_texture (XPM file format)
			∗ South texture(Güney dokusu):
	Usage: ->	SO ./path_to_the_south_texture (XPM file format)
			∗ West texture(Batı dokusu):
	Usage: ->	WE ./path_to_the_west_texture (XPM file format)
			∗ East texture(Doğu dokusu):
	Usage: ->	EA ./path_to_the_east_texture (XPM file format)
			∗ Zemin rengi: (R,G,B [0,255] aralığında: 0, 255, 255)
	Usage: ->	F 220,100,0
			∗ İç kaplama rengi: (R,G,B [0,255] aralığında: 0, 255, 255)
	Usage: ->	C 225,30,0
		◦ Dosyada herhangi bir yanlış yapılandırma ile karşılaşılırsa,
	 program düzgün bir şekilde kapanmalı ve seçtiğiniz açık bir hata
	 mesajının ardından "Error\n" döndürmelidir.

------------------------- BONUS PART -------------------------

Bonus listesi:
	• Duvar çarpmaları.
	• Mini harita sistemi.
	• Açılıp kapanabilen kapılar.
	• Animasyonlu spritelar.
	• Mouse yardımıyla bakış açısını değiştirme.

INFO: Değerlendirmeniz sırasında kullanımları serbest olduğu sürece,
bonus bölümünü tamamlamak için başka fonksiyonları kullanmanıza veya
haritaya semboller eklemenize izin verilmektedir.  Ayrıca, istenen
harita dosyası formatını ihtiyaçlarınıza göre değiştirebilirsiniz.
Akıllı davranın!

* ************************************************************************** *
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
	t_main	main;
	printf("Program started: Argumans checking...\n");
	if (argv_check(argc, argv[1], &main) == ERROR)
		return (1);
	printf("Argumans checked OK: Initializing cub3D...\n");
	if (init_all(&main) == ERROR)
		return (2);
	printf("Initializing cub3D OK: Setting MLX window to screen...\n");
	if (window_set(&main) == ERROR)
		return (3);
	mlx_loop(main.mlx->ptr);// Burada mlx'le actigimiz window'umuzun kapanmamasi icin donguye alacagiz. Her sey bu window set ile mlx_loop() arasinda ilerleyecek.
	free(main.texture.rgb_f);
	free(main.texture.rgb_c);
	free_definitions(&main);
	free_pstr(main.map);
	return (0);
}
