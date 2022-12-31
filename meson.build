# SPDX-FileCopyrightText: 2021 Andrea Pappacoda
#
# SPDX-License-Identifier: BSD-3-Clause

project(
	'xbyak_riscv',
	'cpp',
	version: '6.68',
	license: 'BSD-3-Clause',
	default_options: 'b_ndebug=if-release'
)

install_subdir('xbyak_riscv', install_dir: get_option('includedir'))

xbyak_riscv_dep = declare_dependency(include_directories: include_directories('.'))

if meson.version().version_compare('>=0.54.0')
	meson.override_dependency(meson.project_name(), xbyak_riscv_dep)
endif

import('pkgconfig').generate(
	name: meson.project_name(),
	description: 'JIT assembler for RISC-V',
	version: meson.project_version(),
	url: 'https://github.com/herumi/xbyak_riscv'
)

if meson.version().version_compare('>=0.50.0')
	cmake = import('cmake')

	cmake.write_basic_package_version_file(
		name: meson.project_name(),
		version: meson.project_version()
	)

	cmake_conf = configuration_data()
	cmake_conf.set('TARGET_NAME', meson.project_name() + '::' + meson.project_name())
	cmake_conf.set('ABSOLUTE_INCLUDE_DIR', get_option('prefix')/get_option('includedir'))

	cmake.configure_package_config_file(
		name: meson.project_name(),
		input: 'cmake'/'meson-config.cmake.in',
		configuration: cmake_conf
	)
endif
