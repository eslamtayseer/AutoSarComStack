project ('autosar', 'c')

resources = ['main.c',
             'Com/Com.c',
             'Com/Com_Lcfg.c',
             'Com/Com_Pbcfg.c',
             'PduR/PduR.c',
             'CanIf/CanIf.c',
             'CanIf/CanIf_Cfg.c',
             'Can_Calipso/Can_PBcfg.c']
             
incdir = include_directories('include')
Comdir = include_directories('Com')
PduRdir = include_directories('PduR')
CanIfdir = include_directories('CanIf')
Can_Calipsodir = include_directories('Can_Calipso')
Can_Tivadir = include_directories('Can_Tiva')

executable ('autosar',
            resources,
            include_directories : [incdir, Comdir, PduRdir, CanIfdir, Can_Calipsodir, Can_Tivadir],
            link_args : '-lm',
            install : true)

