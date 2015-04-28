/* Generated automatically by the program 'build/genpreds'
   from the machine description file '/Volumes/ct-ng/.build/src/gcc-4.9.1/gcc/config/m68k/m68k.md'.  */

#ifndef GCC_TM_PREDS_H
#define GCC_TM_PREDS_H

#ifdef HAVE_MACHINE_MODES
extern int general_operand (rtx, enum machine_mode);
extern int address_operand (rtx, enum machine_mode);
extern int register_operand (rtx, enum machine_mode);
extern int pmode_register_operand (rtx, enum machine_mode);
extern int scratch_operand (rtx, enum machine_mode);
extern int immediate_operand (rtx, enum machine_mode);
extern int const_int_operand (rtx, enum machine_mode);
extern int const_double_operand (rtx, enum machine_mode);
extern int nonimmediate_operand (rtx, enum machine_mode);
extern int nonmemory_operand (rtx, enum machine_mode);
extern int push_operand (rtx, enum machine_mode);
extern int pop_operand (rtx, enum machine_mode);
extern int memory_operand (rtx, enum machine_mode);
extern int indirect_operand (rtx, enum machine_mode);
extern int ordered_comparison_operator (rtx, enum machine_mode);
extern int comparison_operator (rtx, enum machine_mode);
extern int general_src_operand (rtx, enum machine_mode);
extern int nonimmediate_src_operand (rtx, enum machine_mode);
extern int memory_src_operand (rtx, enum machine_mode);
extern int not_sp_operand (rtx, enum machine_mode);
extern int pcrel_address (rtx, enum machine_mode);
extern int const_uint32_operand (rtx, enum machine_mode);
extern int const_sint32_operand (rtx, enum machine_mode);
extern int valid_dbcc_comparison_p (rtx, enum machine_mode);
extern int m68k_cstore_comparison_operator (rtx, enum machine_mode);
extern int extend_operator (rtx, enum machine_mode);
extern int symbolic_operand (rtx, enum machine_mode);
extern int const_call_operand (rtx, enum machine_mode);
extern int call_operand (rtx, enum machine_mode);
extern int const_sibcall_operand (rtx, enum machine_mode);
extern int sibcall_operand (rtx, enum machine_mode);
extern int post_inc_operand (rtx, enum machine_mode);
extern int pre_dec_operand (rtx, enum machine_mode);
extern int const0_operand (rtx, enum machine_mode);
extern int const1_operand (rtx, enum machine_mode);
extern int m68k_subword_comparison_operand (rtx, enum machine_mode);
extern int movsi_const0_operand (rtx, enum machine_mode);
extern int non_symbolic_call_operand (rtx, enum machine_mode);
extern int fp_src_operand (rtx, enum machine_mode);
#endif /* HAVE_MACHINE_MODES */

#define CONSTRAINT_NUM_DEFINED_P 1
enum constraint_num
{
  CONSTRAINT__UNKNOWN = 0,
  CONSTRAINT_a,
  CONSTRAINT_d,
  CONSTRAINT_f,
  CONSTRAINT_I,
  CONSTRAINT_J,
  CONSTRAINT_K,
  CONSTRAINT_L,
  CONSTRAINT_M,
  CONSTRAINT_N,
  CONSTRAINT_O,
  CONSTRAINT_P,
  CONSTRAINT_R,
  CONSTRAINT_G,
  CONSTRAINT_H,
  CONSTRAINT_S,
  CONSTRAINT_T,
  CONSTRAINT_Q,
  CONSTRAINT_U,
  CONSTRAINT_W,
  CONSTRAINT_Cs,
  CONSTRAINT_Ci,
  CONSTRAINT_C0,
  CONSTRAINT_Cj,
  CONSTRAINT_Cu,
  CONSTRAINT_CQ,
  CONSTRAINT_CW,
  CONSTRAINT_CZ,
  CONSTRAINT_CS,
  CONSTRAINT_Ap,
  CONSTRAINT_Ac,
  CONSTRAINT__LIMIT
};

extern enum constraint_num lookup_constraint (const char *);
extern bool constraint_satisfied_p (rtx, enum constraint_num);

static inline size_t
insn_constraint_len (char fc, const char *str ATTRIBUTE_UNUSED)
{
  switch (fc)
    {
    case 'A': return 2;
    case 'C': return 2;
    default: break;
    }
  return 1;
}

#define CONSTRAINT_LEN(c_,s_) insn_constraint_len (c_,s_)

extern enum reg_class regclass_for_constraint (enum constraint_num);
#define REG_CLASS_FROM_CONSTRAINT(c_,s_) \
    regclass_for_constraint (lookup_constraint (s_))
#define REG_CLASS_FOR_CONSTRAINT(x_) \
    regclass_for_constraint (x_)

extern bool insn_const_int_ok_for_constraint (HOST_WIDE_INT, enum constraint_num);
#define CONST_OK_FOR_CONSTRAINT_P(v_,c_,s_) \
    insn_const_int_ok_for_constraint (v_, lookup_constraint (s_))

#define CONST_DOUBLE_OK_FOR_CONSTRAINT_P(v_,c_,s_) \
    constraint_satisfied_p (v_, lookup_constraint (s_))

#define EXTRA_CONSTRAINT_STR(v_,c_,s_) \
    constraint_satisfied_p (v_, lookup_constraint (s_))

extern bool insn_extra_memory_constraint (enum constraint_num);
#define EXTRA_MEMORY_CONSTRAINT(c_,s_) insn_extra_memory_constraint (lookup_constraint (s_))

#define EXTRA_ADDRESS_CONSTRAINT(c_,s_) false

#endif /* tm-preds.h */
