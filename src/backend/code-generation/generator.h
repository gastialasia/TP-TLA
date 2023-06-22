#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "../symbol-table/utils.h"


#define EXTRAS "<features> <apic/> <vmport state=\"off\"/> </features> <cpu mode=\"host-passthrough\"/> <clock offset=\"utc\"> <timer name=\"rtc\" tickpolicy=\"catchup\"/> <timer name=\"pit\" tickpolicy=\"delay\"/> <timer name=\"hpet\" present=\"no\"/> </clock> <pm> <suspend-to-mem enabled=\"no\"/> <suspend-to-disk enabled=\"no\"/> </pm> <metadata> <libosinfo:libosinfo xmlns:libosinfo=\"http://libosinfo.org/xmlns/libvirt/domain/1.0\"> <libosinfo:os id=\"http://fedoraproject.org/fedora/37\"/> </libosinfo:libosinfo> </metadata> <os> <type arch=\"x86_64\" machine=\"q35\">hvm</type> </os>"

#define DISCO "<devices> <emulator>/usr/bin/qemu-system-x86_64</emulator> <disk type=\"file\" device=\"disk\"> <driver name=\"qemu\" type=\"qcow2\" discard=\"unmap\"/> <source file=\"Win%dk.qcow2\"/> <target dev=\"vda\" bus=\"virtio\"/> <boot order=\"2\"/> </disk> <disk type=\"file\" device=\"cdrom\"> <driver name=\"qemu\" type=\"raw\"/> <source file=\"/%s.iso\"/> <target dev=\"sda\" bus=\"sata\"/> <readonly/> <boot order=\"1\"/> </disk> <controller type=\"usb\" model=\"qemu-xhci\" ports=\"15\"/> <controller type=\"pci\" model=\"pcie-root\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <controller type=\"pci\" model=\"pcie-root-port\"/> <interface type=\"network\"> <source network=\"default\"/> <mac address=\"52:54:00:bb:09:42\"/> <model type=\"virtio\"/> </interface> <console type=\"pty\"/> <channel type=\"unix\"> <source mode=\"bind\"/> <target type=\"virtio\" name=\"org.qemu.guest_agent.0\"/> </channel> <channel type=\"spicevmc\"> <target type=\"virtio\" name=\"com.redhat.spice.0\"/> </channel> <input type=\"tablet\" bus=\"usb\"/> <graphics type=\"spice\" port=\"-1\" tlsPort=\"-1\" autoport=\"yes\"> <image compression=\"off\"/> </graphics> <sound model=\"ich9\"/> <video> <model type=\"virtio\"/> </video> <redirdev bus=\"usb\" type=\"spicevmc\"/> <redirdev bus=\"usb\" type=\"spicevmc\"/> <memballoon model=\"virtio\"/> <rng model=\"virtio\"> <backend model=\"random\">/dev/urandom</backend> </rng> </devices>\n"

void Generator(int result);

void generateVmUnion(VmUnion * vmUnion);

void generateVmType (VmType * vmType);

void generateResources(Resources * resources);

void generateResource(Resource * resource);

void generateComponent(Component * component, Expression * expression);

void generateExpression(Expression * expression, ComponentType type);

void generateVariable(Variable * variable, ComponentType type);

void generateUnitNumber(int number, Unit * unit);

int generateUnit(int number, Unit * unit);

void generateCores(Expression * expression);

void generateBios(BiosType * biosType);

void generateNetExp(NetExp * netExp);

void generateNetType(NetType * netType, char * macAddr);

void generateResult(Variable* variable1, Operator* Operator, Variable* variable2);

void generateName(char * vmName);

void generateRam(Expression * expression);

void generateSo(SoResource * soResource);

void generateDisk(Expression * expression);

void addDefaultResources(vmInfo* vmInfo);

void addExtras(vmInfo* vmInfo);

#endif
